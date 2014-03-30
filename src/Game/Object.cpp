//
// Object.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Wed Feb  5 13:27:25 2014 geoffrey bauduin
// Last update Wed Feb 19 00:05:51 2014 geoffrey bauduin
//

#include	<cstddef>
#include	"Game/Object.hpp"
#include	"Threading/ScopeLock.hpp"

Game::Object::Object(void):
  Game::AElement(),
  _mutex(new Mutex),
  _ownerID(0) {

}

Game::Object::~Object(void) {
  delete this->_mutex;
}

void	Game::Object::init(Kernel::ID::id_t id, const Kernel::Serial &serial, int orientation, double x, double y, double z) {
  Game::AElement::init(id, serial, NULL, Game::OBJECT, orientation, x, y, z);
  this->_ownerID = 0;
}

void	Game::Object::destroy(void) {
  Game::AElement::destroy();
}

bool	Game::Object::objectIsBeingCarried(void) const {
  return (this->_ownerID != 0);
}

bool	Game::Object::pickUp(Kernel::ID::id_t owner) {
  ScopeLock s(this->_mutex);
  if (this->objectIsBeingCarried() == false) {
    this->_ownerID = owner;
  }
  return (this->_ownerID == owner);
}

void	Game::Object::release(void) {
  ScopeLock s(this->_mutex);
  this->_ownerID = 0;
}

void	Game::Object::setPosition(double x, double y, double z) {
  ScopeLock s(this->_mutex);
  this->_position.x = x;
  this->_position.y = y;
  this->_position.z = z;
}
