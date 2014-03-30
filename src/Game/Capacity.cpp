//
// Capacity.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Wed Jan 15 14:44:20 2014 geoffrey bauduin
// Last update Fri Mar 14 16:03:02 2014 geoffrey bauduin
//

#include	"Game/Capacity.hpp"
#include	"Threading/ScopeLock.hpp"
#include	"Kernel/CapacityData.hpp"

Game::Capacity::Capacity(void):
  Game::ABase(), _automatic(false), _owner(0), _mutex(new Mutex) {
}

Game::Capacity::~Capacity(void) {
  delete this->_mutex;
}

void	Game::Capacity::init(const std::string &serial, bool automatic, const Game::Player *player, Kernel::ID::id_t owner) {
  Game::ABase::init(serial, ::Game::CAPACITY, player);
  this->_automatic = automatic;
  if (this->_infos.capacity->isAuto) {
    this->_automatic = true;
  }
  this->_owner = owner;
}

void	Game::Capacity::destroy(void) {
  Game::ABase::destroy();
}

void	Game::Capacity::setAutomatic(bool status) {
  ScopeLock s(this->_mutex);
  if (this->_infos.capacity->canAuto && status) {
    this->_automatic = true;
  }
  else {
    this->_automatic = false;
  }
}

Kernel::ID::id_t	Game::Capacity::getOwner(void) const {
  return (this->_owner);
}

bool	Game::Capacity::isAutomatic(void) const {
  return (this->_automatic);
}

bool	Game::Capacity::canBeAutomatic(void) const {
  return (this->_infos.capacity->canAuto);
}
