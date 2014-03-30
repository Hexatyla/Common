//
// ElementRessources.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sun Jan 12 14:07:24 2014 geoffrey bauduin
// Last update Tue Mar 18 13:52:41 2014 geoffrey bauduin
//

#define	ABS(x)	((x) < 0 ? (-x) : (x))
#include	"Kernel/ElementRessources.hpp"
#include	"Threading/ScopeLock.hpp"

Kernel::ElementRessources::ElementRessources(void):
  _mutex(new Mutex), _type(NONE), _life(0), _maxLife(0), _ress(0), _maxRess(0) {

}

Kernel::ElementRessources::~ElementRessources(void) {
  delete this->_mutex;
}

void	Kernel::ElementRessources::init(unsigned int life, Kernel::ElementRessources::Type type, unsigned int ressources, unsigned int maxLife, unsigned int maxRess) {
  this->_ress = ressources;
  this->_type = type;
  this->_life = life;
  this->_maxLife = maxLife;
  this->_maxRess = maxRess;
}

void	Kernel::ElementRessources::destroy(void) {

}

unsigned int	Kernel::ElementRessources::getLife(void) const {
  return (this->_life);
}

void	Kernel::ElementRessources::change(unsigned int *v, unsigned int max, int change) {
  int newV = static_cast<int>(*v);
  newV += change;
  if (newV < 0) {
    *v = 0;
  }
  else if (newV > static_cast<int>(max)) {
    *v = max;
  }
  else {
    *v = static_cast<unsigned int>(newV);
  }
}

void	Kernel::ElementRessources::changeLife(int change) {
  ScopeLock s(this->_mutex);
  this->change(&this->_life, this->_maxLife, change);
}

unsigned int	Kernel::ElementRessources::getRessource(void) const {
  return (this->_ress);
}

Kernel::ElementRessources::Type	Kernel::ElementRessources::getRessourceType(void) const {
  return (this->_type);
}

void	Kernel::ElementRessources::changeRessource(int change) {
  ScopeLock s(this->_mutex);
  this->change(&this->_ress, this->_maxRess, change);
}

bool	Kernel::ElementRessources::hasEnough(const Kernel::ElementRessources &rhs) const {
  ScopeLock s(this->_mutex);
  return (rhs._type == this->_type && this->_life >= rhs._life && this->_ress >= rhs._ress);
}

void	Kernel::ElementRessources::setLife(unsigned int amount) {
  ScopeLock s(this->_mutex);
  this->_life = amount;
}

void	Kernel::ElementRessources::setRessources(unsigned int amount) {
  ScopeLock s(this->_mutex);
  this->_ress = amount;
}
