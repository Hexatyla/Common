//
// NoDeleteWhileUsedByAThread.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Tue Mar  4 18:30:37 2014 geoffrey bauduin
// Last update Wed Mar  5 11:26:13 2014 geoffrey bauduin
//

#include	"NoDeleteWhileUsedByAThread.hpp"
#include	"Threading/ScopeLock.hpp"

NoDeleteWhileUsedByAThread::NoDeleteWhileUsedByAThread(void):
  _mutex(new Mutex), _deleting(false), _cond(new CondVar), _nbr(0) {

}

NoDeleteWhileUsedByAThread::~NoDeleteWhileUsedByAThread(void) {
  delete this->_mutex;
  delete this->_cond;
}

void	NoDeleteWhileUsedByAThread::init(void) {
  this->_deleting = false;
  this->_nbr = 0;
}

void	NoDeleteWhileUsedByAThread::destroy(void) {}

bool	NoDeleteWhileUsedByAThread::lock(void) {
  if (this->_deleting == true) {
    return (false);
  }
  ScopeLock s(this->_mutex);
  if (this->_deleting == true) {
    return (false);
  }
  this->_nbr++;
  return (true);
}

void	NoDeleteWhileUsedByAThread::lockDestroy(void) {
  this->_deleting = true;
  while (this->_nbr > 0) {
    this->_cond->wait();
  }
}

void	NoDeleteWhileUsedByAThread::unlock(void) {
  ScopeLock s(this->_mutex);
  this->_nbr--;
  if (this->_nbr <= 0) {
    this->_cond->signal();
  }
}
