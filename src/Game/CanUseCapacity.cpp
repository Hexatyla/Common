//
// CanUseCapacity.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Fri Feb 21 11:03:04 2014 geoffrey bauduin
// Last update Wed Mar 26 10:57:10 2014 geoffrey bauduin
//

#include	"Game/CanUseCapacity.hpp"
#include	"Threading/ScopeLock.hpp"
#include	"Kernel/CapacityData.hpp"

Game::CanUseCapacity::CanUseCapacity(void):
  _mutex(new Mutex),
  _target(0), _targetType(::Game::NONE), _isAttacking(false), _targetZone(0.0, 0.0, 0.0),
  _attackCapacity(""), _attackZoneCapacity("") {

}

Game::CanUseCapacity::~CanUseCapacity(void) {
  delete this->_mutex;
}

void	Game::CanUseCapacity::init(void) {
  this->_target = 0;
  this->_targetType = ::Game::NONE;
  this->_isAttacking = false;
  this->_attackCapacity = "";
  this->_attackZoneCapacity = "";
  for (auto it : this->_capacities) {
    if (it.second->canBeAutomatic() && it.second->isAutomatic()) {
      switch(it.second->getInfos().capacity->target) {
      case Game::Capacity::ZONE:
	this->_attackZoneCapacity = it.second->serial();
	break;
      case Game::Capacity::ITEM:
	this->_attackCapacity = it.second->serial();
	break;
      default:
	break;
      }
    }
  }
}

void	Game::CanUseCapacity::destroy(void) {
}

bool	Game::CanUseCapacity::isAttacking(void) const {
  ScopeLock s(this->_mutex);
  return (this->_isAttacking);
}

Kernel::ID::id_t	Game::CanUseCapacity::getTarget(void) const {
  ScopeLock s(this->_mutex);
  return (this->_target);
}

::Game::Type	Game::CanUseCapacity::getTargetType(void) const {
  ScopeLock s(this->_mutex);
  return (this->_targetType);
}

void	Game::CanUseCapacity::setTarget(double x, double y, double z) {
  ScopeLock s(this->_mutex);
  this->_targetZone.x = x;
  this->_targetZone.y = y;
  this->_targetZone.z = z;
  this->_isAttacking = true;
}

void	Game::CanUseCapacity::setTarget(Kernel::ID::id_t id, ::Game::Type type) {
  ScopeLock s(this->_mutex);
  this->_target = id;
  this->_targetType = type;
  this->_isAttacking = true;
}

void	Game::CanUseCapacity::removeTarget(void) {
  ScopeLock s(this->_mutex);
  this->_isAttacking = false;
}

void	Game::CanUseCapacity::attack(const Game::AElement *) {}

const Kernel::Serial	&Game::CanUseCapacity::getAttackCapacity(void) const {
  return (this->_attackCapacity);
}

const Kernel::Serial	&Game::CanUseCapacity::getAttackZoneCapacity(void) const {
  return (this->_attackZoneCapacity);
}
