//
// CondVar.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Jan 21 09:51:54 2014 geoffrey bauduin
// Last update Thu Jan 23 13:26:03 2014 geoffrey bauduin
//

#include	<time.h>
#include	<errno.h>
#include	"Threading/CondVar.hpp"
#include	"Threading/ScopeLock.hpp"

CondVar::CondVar(void):
  _mutex(), _cond() {
  pthread_cond_init(&this->_cond, NULL);
}

CondVar::~CondVar(void) {
  pthread_cond_destroy(&this->_cond);
}

bool	CondVar::timewait(unsigned int ms) {
  timespec t;
  t.tv_sec = time(NULL) + ms / 1000;
  t.tv_nsec = (ms % 1000) * 1000000;
  int ret;
  {
    ScopeLock s(&this->_mutex);
    ret = pthread_cond_timedwait(&this->_cond, this->_mutex.getMutex(), &t);
  }
  return (ret == ETIMEDOUT ? true : false);
}

void	CondVar::wait(void) {
  ScopeLock s(&this->_mutex);
  pthread_cond_wait(&this->_cond, this->_mutex.getMutex());
}

void	CondVar::signal(void) {
  pthread_cond_signal(&this->_cond);
}

void	CondVar::broadcast(void) {
  pthread_cond_broadcast(&this->_cond);
}

