//
// RessourcesSpot.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Mon Feb 10 12:05:13 2014 geoffrey bauduin
// Last update Tue Mar 25 11:40:10 2014 geoffrey bauduin
//

#include	<algorithm>
#include	"Game/RessourcesSpot.hpp"
#include	"Threading/ScopeLock.hpp"
#include	"Kernel/Config.hpp"

Game::RessourcesSpot::RessourcesSpot(void):
  Game::AElement(),
  _type(Game::Ressources::WOOD), _capacity(), _harvesters(), _mutex(new Mutex) {
}

Game::RessourcesSpot::~RessourcesSpot(void) {
  delete this->_mutex;
}

void	Game::RessourcesSpot::init(Kernel::ID::id_t id, double x, double y, double z, Game::Ressources::Type type, unsigned int amount) {
  const Kernel::Serial serial = type == Game::Ressources::GOLD ?
    Kernel::Config::getInstance()->getString(Kernel::Config::GOLD_SPOT_SERIAL) :
    Kernel::Config::getInstance()->getString(Kernel::Config::WOOD_SPOT_SERIAL);
  ::Game::AElement::init(id, serial, NULL, ::Game::RESSSPOT, 0, x, y, z);
  this->_capacity.init(0, 0, 0);
  if (amount == 0) {
    amount = Kernel::Config::getInstance()->getUInt(Kernel::Config::RESSOURCES_SPOT_DEFAULT_CAPACITY);
  }
  this->_capacity.set(type, amount);
  this->_type = type;
}

void	Game::RessourcesSpot::destroy(void) {
  ::Game::AElement::destroy();
  this->_capacity.destroy();
  this->_harvesters.clear();
}

void	Game::RessourcesSpot::addHarvester(Kernel::ID::id_t id, unsigned int) {
  ScopeLock s(this->_mutex);
  this->_harvesters.push_back(id);
}

void	Game::RessourcesSpot::removeHarvester(Kernel::ID::id_t id) {
  ScopeLock s(this->_mutex);
  this->_harvesters.remove(id);
}

const std::list<Kernel::ID::id_t> &Game::RessourcesSpot::getHarvesters(void) const {
  ScopeLock s(this->_mutex);
  return (this->_harvesters);
}

bool	Game::RessourcesSpot::canBeHarvested(void) const {
  ScopeLock s(this->_mutex);
  return (this->_harvesters.size() < Kernel::Config::getInstance()->getUInt(Kernel::Config::MAX_HARVESTERS_ON_SPOT));
}

bool	Game::RessourcesSpot::isHarvesting(Kernel::ID::id_t id) const {
  ScopeLock s(this->_mutex);
  return (std::find(this->_harvesters.begin(), this->_harvesters.end(), id) != this->_harvesters.end());
}

Game::Ressources::Type Game::RessourcesSpot::getSpotType(void) const {
  return (this->_type);
}

void	Game::RessourcesSpot::setAmount(unsigned int amount) {
  this->_capacity.set(this->_type, amount);
}

unsigned int	Game::RessourcesSpot::getAmount(void) const {
  return (this->_capacity.get(this->_type));
}
