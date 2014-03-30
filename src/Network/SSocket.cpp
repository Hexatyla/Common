//
// SSocket.cpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 10 16:20:20 2014 gautier lefebvre
// Last update Tue Mar 18 16:33:22 2014 gautier lefebvre
//

#include	<unistd.h>
#include	"Network/Socket.hpp"
#include	"Threading/ScopeLock.hpp"
#include	"Factory/Protocol.hpp"

#define		LOCK_SOCKET	ScopeLock scopelocksocket(this)

Network::SSocket::SSocket():
  Mutex::Mutex(),
  Network::Socket::Socket()
{}

Network::SSocket::~SSocket() {}

void		Network::SSocket::destroy() {
  LOCK_SOCKET;
  ::close(this->_socket);
  for (auto job : this->_output) {
    Factory::Protocol::Job::remove(job);
  }
  for (auto job : this->_input) {
    Factory::Protocol::Job::remove(job);
  }

  this->_socket = -1;
  this->_output.clear();
  this->_input.clear();
  this->_offsetI = 0;
  this->_offsetO = 0;
  this->_brokenPipe = false;
}

void		Network::SSocket::init() {
  LOCK_SOCKET;
  this->_socket = -1;
  this->_output.clear();
  this->_input.clear();
  this->_offsetI = 0;
  this->_offsetO = 0;  
  this->_brokenPipe = false;
}

bool		Network::SSocket::hasNewJob() {
  LOCK_SOCKET;
  return (Network::Socket::hasNewJob());
}

bool		Network::SSocket::hasSomethingToSend() {
  LOCK_SOCKET;
  return (Network::Socket::hasSomethingToSend());
}

int		Network::SSocket::getFD() {
  LOCK_SOCKET;
  return (Network::Socket::getFD());
}

Protocol::Job*	Network::SSocket::getNextJob() {
  LOCK_SOCKET;
  return (Network::Socket::getNextJob());
}

void		Network::SSocket::push(Protocol::Job* job) {
  LOCK_SOCKET;
  Network::Socket::push(job);
}

void		Network::SSocket::create() {
  LOCK_SOCKET;
  Network::Socket::create();
}

void		Network::SSocket::connect(const std::string &host, int port) {
  LOCK_SOCKET;
  Network::Socket::connect(host, port);
}

void		Network::SSocket::bind(int port) {
  LOCK_SOCKET;
  Network::Socket::bind(port);
}

void		Network::SSocket::listen(int i) {
  LOCK_SOCKET;
  Network::Socket::listen(i);
}

void		Network::SSocket::accept(Socket *socket) {
  LOCK_SOCKET;
  Network::Socket::accept(socket);
}

void		Network::SSocket::recv() {
  LOCK_SOCKET;
  Network::Socket::recv();
}

void		Network::SSocket::send() {
  LOCK_SOCKET;
  Network::Socket::send();
}
