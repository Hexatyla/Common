//
// Thread.hpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 10 14:20:07 2014 gautier lefebvre
// Last update Fri Jan 10 16:21:14 2014 gautier lefebvre
//

#ifndef		__THREAD_HPP__
#define		__THREAD_HPP__

#include	<pthread.h>

class		Thread {
private:
  pthread_t	_t;

public:
  Thread();
  virtual ~Thread();

  bool		start(void *(*)(void*), void*);
  void		wait();
  void		exit(void*);
};

#endif
