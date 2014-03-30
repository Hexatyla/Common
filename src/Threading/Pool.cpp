//
// Pool.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Jan 21 10:20:06 2014 geoffrey bauduin
// Last update Sat Mar 22 15:11:15 2014 geoffrey bauduin
//

#include	<cstddef>
#include	<unistd.h>
#include	"Threading/Pool.hpp"
#include	"Logger.hpp"

ThreadPool::ThreadPool(unsigned int th): _th(), _number(0) {
  if (th == DEFINE_FOR_ME) {
    th = sysconf(_SC_NPROCESSORS_ONLN) * THREADS_PER_CORE;
  }
  th++;
  Logger::getInstance()->logf("Launching %d threads...", Logger::INFORMATION, th);
  this->_th.assign(th, NULL);
  for (unsigned int i = 0 ; i < th ; ++i) {
    this->_th[i] = new Thread;
  }
  this->_number = th;
}

ThreadPool::~ThreadPool(void) {
  this->wait();
  for (auto it : this->_th) {
    delete it;
  }
}

bool	ThreadPool::start(void *(*func)(void *), void *param) {
  for (auto it : this->_th) {
    if (!it->start(func, param)) {
      return (false);
    }
  }
  return (true);
}

unsigned int	ThreadPool::getNumberOfThreads(void) const {
  return (this->_number);
}

void	ThreadPool::wait(void) {
  for (auto it : this->_th) {
    it->wait();
  }
}

