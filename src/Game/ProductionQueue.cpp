//
// ProductionQueue.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Thu Feb  6 13:40:04 2014 geoffrey bauduin
// Last update Fri Mar 21 13:58:59 2014 geoffrey bauduin
//

#include	<algorithm>
#include	"Game/ProductionQueue.hpp"
#include	"Threading/ScopeLock.hpp"

Game::ProductionQueue::ProductionQueue(void):
  _queue(), _mutex(new Mutex) {

}

Game::ProductionQueue::~ProductionQueue(void) {
  delete this->_mutex;
}

void	Game::ProductionQueue::init(void) {
}

void	Game::ProductionQueue::destroy(void) {
  this->_queue.clear();
}

const Kernel::Serial &Game::ProductionQueue::front(void) const {
  ScopeLock s(this->_mutex);
  return (this->_queue.front());
}

const Kernel::Serial &Game::ProductionQueue::back(void) const {
  ScopeLock s(this->_mutex);
  return (this->_queue.back());
}

unsigned int	Game::ProductionQueue::size(void) const {
  ScopeLock s(this->_mutex);
  return (this->_queue.size());
}

bool	Game::ProductionQueue::empty(void) const {
  ScopeLock s(this->_mutex);
  return (this->_queue.empty());
}

const Kernel::Serial	&Game::ProductionQueue::at(unsigned int pos) const {
  ScopeLock s(this->_mutex);
  return (this->_queue.at(pos));
}

const Kernel::Serial	Game::ProductionQueue::pop(void) {
  ScopeLock s(this->_mutex);
  Kernel::Serial serial = this->_queue.front();
  this->_queue.pop_front();
  return (serial);
}

void	Game::ProductionQueue::push(const Kernel::Serial &serial) {
  ScopeLock s(this->_mutex);
  this->_queue.push_back(serial);
}

void	Game::ProductionQueue::insert(const Kernel::Serial &serial, unsigned int pos) {
  ScopeLock s(this->_mutex);
  auto it = this->_queue.begin();
  if (pos < this->size()) {
    it += pos;
  }
  else {
    it = this->_queue.end();
  }
  this->_queue.insert(it, serial);
}

bool	Game::ProductionQueue::remove(const Kernel::Serial &serial) {
  ScopeLock s(this->_mutex);
  for (auto it = this->_queue.rbegin() ; it != this->_queue.rend() ; ++it) {
    if (*it == serial) {
      this->_queue.erase(--it.base());
      return (true);
    }
  }
  return (false);
}

bool	Game::ProductionQueue::contains(const Kernel::Serial &serial) const {
  ScopeLock s(this->_mutex);
  return (std::find(this->_queue.begin(), this->_queue.end(), serial) != this->_queue.end());
}

const std::deque<Kernel::Serial>	&Game::ProductionQueue::getQueue(void) const {
  return (this->_queue);
}
