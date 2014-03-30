//
// Hero.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 18:29:54 2014 geoffrey bauduin
// Last update Thu Mar 13 17:15:56 2014 geoffrey bauduin
//

#include	"Game/Hero.hpp"
#include	"Kernel/Config.hpp"
#include	"Threading/ScopeLock.hpp"

Game::Hero::Hero(void):
  Game::Unit(),
  _mutex(new Mutex),
  _objects() {

}

Game::Hero::~Hero(void) {
  delete this->_mutex;
}

void	Game::Hero::init(unsigned int id, const std::string &serial, const Game::Player *player, int orientation, double x, double y, double z) {
  Game::Unit::init(id, serial, player, orientation, x, y, z, Game::HERO);
}

void	Game::Hero::destroy(void) {
  Game::Unit::destroy();
#ifndef __SERVER__
  for (auto it : this->_objects) {
    (void) it;
    // Factory::Game::Object::remove(it);
  }
  this->_objects.clear();
#endif
}

void	Game::Hero::addObject(Game::Object *object) {
  ScopeLock s(this->_mutex);
  this->_objects.push_back(object);
}

void	Game::Hero::removeObject(Game::Object *object) {
  ScopeLock s(this->_mutex);
  this->_objects.remove(object);
}

bool	Game::Hero::canPickUpObject(void) const {
  return (this->_objects.size() < Kernel::Config::getInstance()->getUInt(Kernel::Config::HERO_OBJECTS_NUMBER));
}

const std::list<Game::Object *> &Game::Hero::getObjects(void) const {
  return (this->_objects);
}

template<typename T>
static T	getFromData(const Game::Hero *hero, void *addr) {
  T value = 0;
  for (auto it : hero->getObjects()) {
    value += *GET_VAL(it->getInfos().data, addr, T);
  }
  return (value);
}

unsigned int	Game::Hero::getUIntFromData(void *addr) const {
  ScopeLock s(this->_mutex);
  return (::Game::Unit::getUIntFromData(addr) + getFromData<unsigned int>(this, addr));
}

double	Game::Hero::getDoubleFromData(void *addr) const {
  ScopeLock s(this->_mutex);
  return (::Game::Unit::getDoubleFromData(addr) + getFromData<double>(this, addr));
}
