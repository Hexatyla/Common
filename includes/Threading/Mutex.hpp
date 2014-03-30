//
// Mutex.hpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 10 14:08:05 2014 gautier lefebvre
// Last update Fri Mar  7 16:14:10 2014 gautier lefebvre
//

#ifndef		__MUTEX_HPP__
#define		__MUTEX_HPP__

#include	<pthread.h>

class		Mutex {
private:
  pthread_mutex_t	_m;

public:
  Mutex();
  virtual ~Mutex();

  void		lock();
  void		unlock();
  bool		trylock();
  pthread_mutex_t *getMutex(void);
  const pthread_mutex_t &getMutex(void) const;

};

#endif
