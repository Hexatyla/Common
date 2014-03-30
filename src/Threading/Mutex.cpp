//
// Mutex.cpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 10 14:14:22 2014 gautier lefebvre
// Last update Fri Mar  7 16:14:43 2014 gautier lefebvre
//

#include	"Threading/Mutex.hpp"

Mutex::Mutex():
  _m() {
  pthread_mutex_init(&(this->_m), NULL);
}

Mutex::~Mutex() {
  pthread_mutex_destroy(&(this->_m));
}

void		Mutex::lock() {
  pthread_mutex_lock(&(this->_m));
}

void		Mutex::unlock() {
  pthread_mutex_unlock(&(this->_m));
}

bool		Mutex::trylock() {
  return (pthread_mutex_trylock(&(this->_m)) == 0);
}

pthread_mutex_t *Mutex::getMutex(void) {
  return (&this->_m);
}

const pthread_mutex_t &Mutex::getMutex(void) const {
  return (this->_m);
}
