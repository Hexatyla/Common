//
// ID.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Mon Jan 20 10:53:45 2014 geoffrey bauduin
// Last update Wed Mar  5 00:25:01 2014 geoffrey bauduin
//

#include	"Kernel/ID.hpp"
#include	"Threading/ScopeLock.hpp"

Kernel::ID::ID(void):
  _data() {
  this->_data[PLAYER] = new Kernel::ID::data;
  this->_data[ITEM] = new Kernel::ID::data;
  this->_data[GAME] = new Kernel::ID::data;
}

Kernel::ID::~ID(void) {
  for (auto it : this->_data) {
    delete it.second;
  }
}

unsigned int	Kernel::ID::get(std::queue<Kernel::ID::id_t> &pool, Kernel::ID::id_t &current) {
  if (pool.size() < 50) {
    current++;
    if (current == 0) {
      current++;
    }
    return (current);
  }
  Kernel::ID::id_t v = pool.front();
  pool.pop();
  return (v);
}

void	Kernel::ID::push(Kernel::ID::id_t v, std::queue<Kernel::ID::id_t> &pool) {
  pool.push(v);
}

Kernel::ID::id_t	Kernel::ID::get(Kernel::ID::Type type) {
  ScopeLock s(this->_data[type]->mutex);
  return (this->get(this->_data[type]->pool, this->_data[type]->current));
}

void	Kernel::ID::push(Kernel::ID::id_t id, Kernel::ID::Type type) {
  ScopeLock s(this->_data[type]->mutex);
  this->push(id, this->_data[type]->pool);
}
