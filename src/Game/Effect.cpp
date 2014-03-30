//
// AEffect.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Jan 14 14:54:25 2014 geoffrey bauduin
// Last update Thu Mar 13 17:09:59 2014 geoffrey bauduin
//

#include	<cstddef>
#include	"Game/Effect.hpp"
#include	"Threading/ScopeLock.hpp"

Game::Effect::Effect(void):
  Game::ABase(),
  _mutex(new Mutex),
  _percentage(0.0), _owner(0) {

}

Game::Effect::~Effect(void) {
  delete this->_mutex;
}

void	Game::Effect::init(const Kernel::Serial &serial, const Game::Player *player, Kernel::ID::id_t itemID) {
  Game::ABase::init(serial, ::Game::EFFECT, player);
  this->_percentage = 0.0;
  this->_owner = itemID;
}

void	Game::Effect::destroy(void) {
  Game::ABase::destroy();
}

double	Game::Effect::getPercentage(void) const {
  ScopeLock s(this->_mutex);
  return (this->_percentage);
}

void	Game::Effect::setPercentage(double p) {
  ScopeLock s(this->_mutex);
  this->_percentage = p;
}

Kernel::ID::id_t	Game::Effect::getOwner(void) const {
  return (this->_owner);
}
