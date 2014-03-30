//
// Building.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 18:18:09 2014 geoffrey bauduin
// Last update Wed Mar 26 10:58:48 2014 geoffrey bauduin
//

#include	<algorithm>
#include	"Game/Building.hpp"
#include	"Threading/ScopeLock.hpp"

Game::Building::Building(void):
  Game::AElement(), Game::CanUseCapacity(),
  _mutex(new Mutex), _buildersMutex(new Mutex),
  _queue(), _builders() {

}

Game::Building::~Building(void) {
  delete this->_mutex;
  delete this->_buildersMutex;
}

void	Game::Building::destroy(void) {
  Game::AElement::destroy();
  Game::CanUseCapacity::destroy();
  this->_queue.destroy();
  this->_builders.clear();
}

void	Game::Building::init(unsigned int id, const Kernel::Serial &serial, const Game::Player *player, int orientation, double x, double y, double z) {
  Game::AElement::init(id, serial, player, Game::BUILDING, orientation, x, y, z);
#ifndef __SERVER__
  Game::CanUseCapacity::init();
#endif
  this->_queue.init();
  this->_built = false;
}

void	Game::Building::addToQueue(const Kernel::Serial &serial) {
  this->_queue.push(serial);
}

const Kernel::Serial	&Game::Building::backQueue(void) const {
  return (this->_queue.back());
}

const Kernel::Serial &Game::Building::frontQueue(void) const {
  return (this->_queue.front());
}

void	Game::Building::placeInQueue(const Kernel::Serial &serial, unsigned int pos) {
  this->_queue.insert(serial, pos);
}

bool	Game::Building::removeFromQueue(const Kernel::Serial &serial) {
  ScopeLock s(this->_mutex);
  return (this->_queue.remove(serial));
}

void	Game::Building::popQueue(void) {
  ScopeLock s(this->_mutex);
  (void) this->_queue.pop();
}

void	Game::Building::addBuilder(Kernel::ID::id_t unitID) {
  ScopeLock s(this->_buildersMutex);
  this->_builders.push_back(unitID);
}

void	Game::Building::removeBuilder(Kernel::ID::id_t unitID) {
  ScopeLock s(this->_buildersMutex);
  this->_builders.remove(unitID);
}

void	Game::Building::setBuilt(void) {
  this->_built = true;
}

const Game::ProductionQueue	*Game::Building::getProductionQueue(void) const {
  return (&this->_queue);
}
