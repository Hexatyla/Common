//
// Projectile.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 18:32:55 2014 geoffrey bauduin
// Last update Thu Mar 13 17:39:40 2014 geoffrey bauduin
//

#include	"Game/Projectile.hpp"
#include	"Threading/ScopeLock.hpp"

Game::Projectile::Projectile(void):
  Game::AElement(), Game::Movable(),
  _mutex(new Mutex), _damageAmount(0),
  _sourceID(0), _sourceType(::Game::NONE),
  _targetID(0), _targetType(::Game::NONE) {

}

Game::Projectile::~Projectile(void) {
  delete this->_mutex;
}

void	Game::Projectile::init(unsigned int id, const std::string &serial, const Game::Player *player, int orientation, double x, double y, double z) {
  Game::AElement::init(id, serial, player, Game::PROJECTILE, orientation, x, y, z);
  Game::Movable::init(orientation, x, y, z);
  this->_damageAmount = 0;
  this->_targetID = 0;
  this->_targetType = ::Game::NONE;
  this->_critChance = 0.0;
}

void	Game::Projectile::destroy(void) {
  Game::AElement::destroy();
  Game::Movable::destroy();
}

void	Game::Projectile::setSource(const ::Game::AElement *source) {
  ScopeLock s(this->_mutex);
  this->_damageAmount = source->getAttack();
  this->_sourceID = source->getID();
  this->_sourceType = source->getType();
  this->_critChance = source->getCritChance();
}

void	Game::Projectile::setTarget(const ::Game::AElement *target) {
  ScopeLock s(this->_mutex);
  this->_targetID = target->getID();
  this->_targetType = target->getType();
  this->_targetingItem = true;
}

unsigned int	Game::Projectile::getAttack(void) const {
  ScopeLock s(this->_mutex);
  return (Game::ABase::getAttack() + this->_damageAmount);
}

Kernel::ID::id_t	Game::Projectile::getTargetID(void) const {
  return (this->_targetID);
}

::Game::Type	Game::Projectile::getTargetType(void) const {
  return (this->_targetType);
}

Kernel::ID::id_t	Game::Projectile::getSourceID(void) const {
  return (this->_sourceID);
}

::Game::Type	Game::Projectile::getSourceType(void) const {
  return (this->_sourceType);
}

double	Game::Projectile::getCritChance(void) const {
  return (this->_critChance);
}

void	Game::Projectile::setTarget(double x, double y, double z) {
  ScopeLock s(this->_mutex);
  this->_target.x = x;
  this->_target.y = y;
  this->_target.z = z;
  this->_targetingItem = false;
}

const Vector3d	&Game::Projectile::getTarget(void) const {
  return (this->_target);
}
