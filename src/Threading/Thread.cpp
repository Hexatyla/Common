//
// Thread.cpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 10 14:22:45 2014 gautier lefebvre
// Last update Sun Mar  9 01:45:43 2014 geoffrey bauduin
//

#include	"Threading/Thread.hpp"

Thread::Thread():
  _t() {}

Thread::~Thread() {
  //  pthread_cancel(this->_t);
}

bool		Thread::start(void *(*func)(void*), void *arg) {
  return (pthread_create(&(this->_t), NULL, func, arg) == 0);
}

void		Thread::wait() {
  pthread_join(this->_t, NULL);
}

void		Thread::exit(void *arg) {
  pthread_exit(arg);
}
