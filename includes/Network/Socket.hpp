//
// Socket.hpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 10 14:31:57 2014 gautier lefebvre
// Last update Tue Mar 18 16:38:16 2014 gautier lefebvre
//

#ifndef		__NETWORK_SOCKET_HPP__
#define		__NETWORK_SOCKET_HPP__

#include	<string>
#include	<list>

#include	"Protocol/Job.hpp"
#include	"Threading/Mutex.hpp"
#include	"IFromFactory.hpp"

namespace	Network {
  class		Socket {
  protected:
    int			_socket;
    std::list<Protocol::Job*>	_input;
    std::list<Protocol::Job*>	_output;
    size_t		_offsetI;
    size_t		_offsetO;
    bool		_brokenPipe;

  public:
    Socket();
    virtual ~Socket();

    virtual bool	hasNewJob() const;
    virtual bool	hasSomethingToSend() const;
    virtual int		getFD() const;

    virtual Protocol::Job*	getNextJob();

    virtual void	push(Protocol::Job*);

    virtual void	create();
    virtual void	connect(const std::string&, int);
    virtual void	bind(int) const;
    virtual void	listen(int) const;
    virtual void	accept(Socket *) const;
    virtual void	recv();
    virtual void	send();

    bool		isBrokenPipe() const;
    void		brokenpipe();
  };

  class		SSocket :public Mutex, public Socket, virtual public IFromFactory {
  public:
    SSocket();
    virtual ~SSocket();

    virtual void	destroy();
    void		init();

    bool		hasNewJob();
    bool		hasSomethingToSend();
    int			getFD();

    virtual Protocol::Job*	getNextJob();
    virtual void	push(Protocol::Job*);

    virtual void	create();
    virtual void	connect(const std::string&, int);
    void		bind(int);
    void		listen(int);
    void		accept(Socket *);
    virtual void	recv();
    virtual void	send();
  };
}

#endif
