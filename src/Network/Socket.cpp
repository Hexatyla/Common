//
// Socket.cpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 10 14:50:03 2014 gautier lefebvre
// Last update Tue Mar 18 16:38:46 2014 gautier lefebvre
//

#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netdb.h>
#include	<arpa/inet.h>
#include	<unistd.h>
#include	<errno.h>
#include	<cstring>

#include	"Network/Socket.hpp"
#include	"Network/Exception.hpp"
#include	"Factory/Protocol.hpp"
#include	"Converter.hpp"

Network::Socket::Socket():
  _socket(-1),
  _input(),
  _output(),
  _offsetI(0),
  _offsetO(0),
  _brokenPipe(false)
{}

Network::Socket::~Socket() {
  if (this->_socket != -1) {
    ::close(this->_socket);
  }
  for (auto job : this->_output) {
    Factory::Protocol::Job::remove(job);
  }
  for (auto job : this->_input) {
    Factory::Protocol::Job::remove(job);
  }
}

bool		Network::Socket::hasNewJob() const { return (this->_input.empty() == false && (this->_offsetI == 0 || this->_input.size() > 1)); }
bool		Network::Socket::hasSomethingToSend() const { return (this->_output.empty() == false); }
int		Network::Socket::getFD() const { return (this->_socket); }
void		Network::Socket::push(Protocol::Job *job) { this->_output.push_back(job); }
bool		Network::Socket::isBrokenPipe() const { return (this->_brokenPipe); }
void		Network::Socket::brokenpipe() { this->_brokenPipe = true; }

Protocol::Job*	Network::Socket::getNextJob() {
  if (this->hasNewJob() == false) {
    return (NULL);
  }

  Protocol::Job *job = this->_input.front();
  this->_input.pop_front();
  return (job);
}

void		Network::Socket::create() {
  if ((this->_socket = ::socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    throw new Network::Exception(std::string("socket: ") + strerror(errno));
  }
}

void		Network::Socket::connect(const std::string &host, int port) {
  struct hostent *h = NULL;
  struct sockaddr_in sin;

  h = gethostbyname(host.c_str());
  if (!h) {
    throw new Network::Exception("Unknown host: " + host);
  }

  sin.sin_addr = *(reinterpret_cast<struct in_addr *>(h->h_addr));
  sin.sin_port = htons(port);
  sin.sin_family = AF_INET;

  if (::connect(this->_socket, reinterpret_cast<struct sockaddr *>(&sin), sizeof(struct sockaddr)) == -1) {
    throw new Network::Exception(std::string("connect: ") + strerror(errno));
  }
}

void		Network::Socket::bind(int port) const {
  if (port == 80) {
    throw new Network::Exception(std::string("bind: cannot bind port " + Converter::StringOf<int>(port)));
  }

  struct sockaddr_in	sin;

  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(port);

  if (::bind(this->_socket, reinterpret_cast<struct sockaddr*>(&sin), sizeof(sin)) == -1) {
    throw new Network::Exception(std::string("bind: ") + strerror(errno));
  }
}

void		Network::Socket::listen(int nb_clients) const {
  if (::listen(this->_socket, nb_clients) == -1) {
    throw new Network::Exception(std::string("listen: ") + strerror(errno));
  }
}

void		Network::Socket::accept(Network::Socket *socket) const {
  struct sockaddr_in	sin;
  socklen_t		size = sizeof(struct sockaddr_in);

  if ((socket->_socket = ::accept(this->_socket, reinterpret_cast<struct sockaddr*>(&sin), &size)) == -1) {
    throw new Network::Exception(std::string("accept: ") + strerror(errno));
  }
}

void		Network::Socket::recv() {
  Protocol::Job *job;
  int		ret;

  if (this->_offsetI == 0) {
    job = Factory::Protocol::Job::create();
    this->_input.push_back(job);
  }


  job = this->_input.back();
  ret = ::read(this->_socket, reinterpret_cast<char *>(job->getData()) + this->_offsetI, sizeof(Protocol::Job::nJob) - this->_offsetI);

  if (ret == -1) {
    throw new Network::Exception(std::string("read socket: ") + strerror(errno));
  } else if (ret == 0) {
    throw new Network::Exception("Connection closed");
  }

  this->_offsetI += ret;
  this->_offsetI %= sizeof(Protocol::Job::nJob);
}

static Network::Socket *gSocket = NULL;
static Mutex	       gMutex;

void		signal_sigpipe(int) {
  gMutex.lock();

  if (gSocket) {
    gSocket->brokenpipe();
  }

  gMutex.unlock();
}

void		Network::Socket::send() {
  if (this->hasSomethingToSend() == false) {
    return ;
  }

  if (this->_brokenPipe == true) {
    throw new Network::Exception(std::string("write socket: broken pipe"));
  }

  gMutex.lock();
  gSocket = this;
  gMutex.unlock();

  Protocol::Job *job = this->_output.front();
  int		ret;

  ret = ::write(this->_socket, reinterpret_cast<char *>(job->getData()) + this->_offsetO, sizeof(Protocol::Job::nJob) - this->_offsetO);

  gMutex.lock();
  gSocket = NULL;
  gMutex.unlock();

  if (ret == -1) {
    throw new Network::Exception(std::string("write socket: ") + strerror(errno));
  }

  if (static_cast<size_t>(ret) + this->_offsetO == sizeof(Protocol::Job::nJob)) {
    Factory::Protocol::Job::remove(job);
    this->_output.pop_front();
  }

  this->_offsetO += ret;
  this->_offsetO %= sizeof(Protocol::Job::nJob);
}
