//
// ScopeLock.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Jan 21 09:59:30 2014 geoffrey bauduin
// Last update Tue Jan 21 10:00:09 2014 geoffrey bauduin
//

#include	"Threading/ScopeLock.hpp"

ScopeLock::ScopeLock(Mutex *mutex):
  _mutex(mutex) {
  this->_mutex->lock();
}

ScopeLock::~ScopeLock(void) {
  this->_mutex->unlock();
}
