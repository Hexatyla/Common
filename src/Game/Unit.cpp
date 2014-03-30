//
// Unit.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 18:25:57 2014 geoffrey bauduin
// Last update Wed Mar 26 10:58:23 2014 geoffrey bauduin
//

#include	"Game/Unit.hpp"
#include	"Threading/ScopeLock.hpp"
#include	"Kernel/Manager.hpp"
#include	"Logger.hpp"

const Game::Unit::levelTable Game::Unit::_xpTable(Game::Unit::createXPTable());

const Game::Unit::levelTable Game::Unit::createXPTable(void) {
  levelTable	xpTable;
  xpTable[1] = {0000, LEVEL_1_DATA};
  xpTable[2] = {0200, LEVEL_2_DATA};
  xpTable[3] = {0450, LEVEL_3_DATA};
  xpTable[4] = {0750, LEVEL_4_DATA};
  xpTable[5] = {1100, LEVEL_5_DATA};
  xpTable[6] = {1500, LEVEL_6_DATA};
  xpTable[7] = {1950, LEVEL_7_DATA};
  xpTable[8] = {2450, LEVEL_8_DATA};
  xpTable[9] = {3000, LEVEL_9_DATA};
  xpTable[10] = {3600, LEVEL_10_DATA};
  return (xpTable);
}

Game::Unit::Unit(void):
  Game::AElement(), Game::Movable(), Game::CanUseCapacity(),
  _stanceMutex(new Mutex), _levelMutex(new Mutex),
  _stance(Game::Stance::NEUTRAL), _carrying(), _xp(0), _level(0),
  _lvlData(NULL), _spot(0) {

}

Game::Unit::~Unit(void) {
  delete this->_stanceMutex;
  delete this->_levelMutex;
}

Kernel::ID::id_t Game::Unit::getSpot(void) const {
  return (this->_spot);
}

void	Game::Unit::init(unsigned int id, const std::string &serial, const Game::Player *player, int orientation, double x, double y, double z, Game::Type type) {
  this->setXPLevel(0, 1);
  Game::AElement::init(id, serial, player, type, orientation, x, y, z);
  Game::Movable::init(orientation, x, y, z);
#ifndef __SERVER__
  Game::CanUseCapacity::init();
#endif
  this->_carrying.init(0, 0, 0);
  this->_stance = Game::Stance::NEUTRAL;
  this->_spot = 0;
}

void	Game::Unit::destroy(void) {
  Game::AElement::destroy();
  Game::Movable::destroy();
  Game::CanUseCapacity::destroy();
  this->_carrying.destroy();
  this->_lvlData = NULL;
}

void	Game::Unit::setStance(Game::Stance::Type stance) {
  ScopeLock s(this->_stanceMutex);
  this->_stance = stance;
}

Game::Stance::Type	Game::Unit::getStance(void) const {
  ScopeLock s(this->_stanceMutex);
  return (this->_stance);
}

void	Game::Unit::addRessources(Game::Ressources::Type type, int amount) {
  this->_carrying.add(type, amount);
}

unsigned int	Game::Unit::getRessources(Game::Ressources::Type type) const {
  return (this->_carrying.get(type));
}

void	Game::Unit::setRessources(Game::Ressources::Type type, unsigned int amount) {
  this->_carrying.set(type, amount);
}

void	Game::Unit::removeRessources(Game::Ressources::Type type, int amount) {
  this->_carrying.set(type, this->_carrying.get(type) - amount);
}

const Game::Ressources &Game::Unit::getRessources(void) const {
  return (this->_carrying);
}

unsigned int	Game::Unit::getXP(void) const {
  ScopeLock s(this->_levelMutex);
  return (this->_xp);
}

unsigned int	Game::Unit::getLevel(void) const {
  ScopeLock s(this->_levelMutex);
  return (this->_level);
}

void	Game::Unit::addXP(unsigned int amount) {
  ScopeLock s(this->_levelMutex);
  this->_xp += amount;
  if (this->_level + 1 <= LEVEL_MAX && this->_xpTable.at(this->_level + 1).xp >= this->_xp) {
    this->setLevel(this->_level + 1);
    this->setXP(this->_xp - this->_xpTable.at(this->_level).xp);
  }
}

void	Game::Unit::setXPLevel(unsigned int xp, unsigned int level) {
  ScopeLock s(this->_levelMutex);
  this->setXP(xp);
  this->setLevel(level);
}

void	Game::Unit::setXP(unsigned int xp) {
  //  ScopeLock s(this->_levelMutex); ---> private
  this->_xp = xp;
}

void	Game::Unit::setLevel(unsigned int level) {
  // ScopeLock s(this->_levelMutex); ----> private
  this->_level = level;
  this->_lvlData = Kernel::Manager::getInstance()->getData(this->_xpTable.at(level).data);
}

unsigned int	Game::Unit::getUIntFromData(void *addr) const {
  return (::Game::AElement::getUIntFromData(addr) + (this->_lvlData ? *GET_VAL(this->_lvlData, addr, unsigned int) : 0));
}

double	Game::Unit::getDoubleFromData(void *addr) const {
  return (::Game::AElement::getDoubleFromData(addr) + (this->_lvlData ? *GET_VAL(this->_lvlData, addr, double) : 0.0));
}

void	Game::Unit::setSpot(Kernel::ID::id_t spotID) {
  this->_spot = spotID;
}
