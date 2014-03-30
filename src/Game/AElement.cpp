//
// AElement.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 17:08:13 2014 geoffrey bauduin
// Last update Wed Mar 26 12:12:27 2014 geoffrey bauduin
//

#include	<cstddef>
#include	"Game/AElement.hpp"
#include	"Game/Player.hpp"
#include	"Kernel/CapacityList.hpp"
#include	"Kernel/Manager.hpp"
#include	"Factory/Game.hpp"
#include	"Logger.hpp"
#include	"Threading/ScopeLock.hpp"

Game::AElement::AElement(void):
  Game::ABase(), HasID(), Game::Position(),
  _actionMutex(new Mutex), _ressourcesMutex(new Mutex), _effectsMutex(new Mutex),
  _ressources(), _capacities(), _speed(0.0),
  _action(NULL), _effects(), _temporaryEffects(),
  _elementMutex(new Mutex), _built() {

}

Game::AElement::~AElement(void) {
  delete this->_elementMutex;
  delete this->_actionMutex;
  delete this->_ressourcesMutex;
  delete this->_effectsMutex;
}

void	Game::AElement::init(Kernel::ID::id_t id, const Kernel::Serial &serial, const Game::Player *player, Game::Type type, int o, double x, double y, double z) {
  Game::ABase::init(serial, type, player);
  HasSerial::init(serial);
  HasInfos::init(serial, type);
  Game::Position::init(o, x, y, z);
  HasID::init(id);
  this->_ressources.init(type == ::Game::BUILDING ? 1 : this->getMaxLife(), this->_infos.data->typeRessources, this->getMaxRessources(),
			 this->getMaxLife(), this->getMaxRessources());
  this->_player = player;
  if (type != Game::RESSSPOT) {
    this->_race = player->getRace();
  }
  else {
    this->_race = NULL;
  }
  this->_type = type;
  this->_speed = this->getSpeed();
  this->_built = true;

#ifndef __SERVER__
  const Kernel::CapacityList *cList = Kernel::Manager::getInstance()->getCapacityList(serial);
  if (cList) {
    for (auto it : cList->list) {
      bool isAuto = Kernel::Manager::getInstance()->getCapacityData(it)->isAuto;
      this->_capacities[it] = Factory::Game::Capacity::create(it, isAuto,
							      this->getPlayer(), this->getID());
    }
  }
#endif

}

void	Game::AElement::destroy(void) {

#ifndef __SERVER__
  for (auto it : this->_effects) {
    for (auto effect : it.second) {
      Factory::Game::Effect::remove(effect);
    }
    it.second.clear();
  }
  this->_effects.clear();
  for (auto it : this->_capacities) {
    Factory::Game::Capacity::remove(it.second);
  }
  this->_capacities.clear();
#endif

  this->_temporaryEffects.clear();
  this->_action = NULL;
  Game::ABase::destroy();
  Game::Position::destroy();
  HasID::destroy();
}

bool	Game::AElement::canPassThrough(const ::Game::AElement *rhs) const {
  ScopeLock s(this->_elementMutex);
  return (true);
  if (rhs == this || this->_infos.data->passthrough & rhs->_type) {
    return (true);
  }
  return (false);
}

void	Game::AElement::setSpeed(unsigned int speed) {
  ScopeLock s(this->_elementMutex);
  this->_speed = speed;
}

unsigned int	Game::AElement::getSpeed(void) const {
  ScopeLock s(this->_elementMutex);
  if (this->_speed != static_cast<unsigned int>(-1)) {
    return (this->_speed);
  }
  return (Game::ABase::getSpeed());
}

unsigned int	Game::AElement::getCurrentLife(void) const {
  ScopeLock s(this->_ressourcesMutex);
  return (this->_ressources.getLife());
}

unsigned int	Game::AElement::getCurrentRessources(void) const {
  ScopeLock s(this->_ressourcesMutex);
  return (this->_ressources.getRessource());
}

const Game::Action	*Game::AElement::getAction(void) const {
  ScopeLock s(this->_actionMutex);
  return (this->_action);
}

void	Game::AElement::setAction(Game::Action *action) {
  ScopeLock s(this->_actionMutex);
  this->_setAction(action);
}

void	Game::AElement::_setAction(Game::Action *action) {
  if (this->_action) {
    this->_stopAction();
  }
  this->_action = action;
}

void	Game::AElement::stopAction(void) {
  ScopeLock s(this->_actionMutex);
  this->_stopAction();
}

void	Game::AElement::_stopAction(void) {
  if (this->_action) {
    Factory::Game::Action::remove(this->_action);
  }
  this->_action = NULL;
}

const Game::AElement::EffectContainer	&Game::AElement::getEffects(void) const {
  ScopeLock s(this->_effectsMutex);
  return (this->_effects);
}

const std::list<const Game::Effect *>	&Game::AElement::getTemporaryEffects(void) const {
  ScopeLock s(this->_effectsMutex);
  return (this->_temporaryEffects);
}

void	Game::AElement::addEffect(const Kernel::Serial &serial) {
  ScopeLock s(this->_effectsMutex);
  Game::Effect *effect = Factory::Game::Effect::create(serial, this->getPlayer(), this->getID());
  this->_effects[serial].push_back(effect);
}

void	Game::AElement::removeEffect(const Kernel::Serial &serial) {
  ScopeLock s(this->_effectsMutex);
  Game::Effect *effect = this->_effects[serial].front();
  this->_effects[serial].pop_front();
  Factory::Game::Effect::remove(effect);
}

const Kernel::ElementRessources	&Game::AElement::getRessources(void) const {
  ScopeLock s(this->_ressourcesMutex);
  return (this->_ressources);
}

bool	Game::AElement::hasCapacity(const Kernel::Serial &serial) const {
  for (auto it : this->_capacities) {
    if (it.first == serial) {
      return (true);
    }
  }
  return (false);
}

bool	Game::AElement::isBuilt(void) const {
  return (this->_built);
}

void	Game::AElement::addLife(unsigned int amount) {
  ScopeLock s(this->_ressourcesMutex);
  this->_ressources.changeLife(static_cast<int>(amount));
}

void	Game::AElement::removeLife(unsigned int amount) {
  ScopeLock s(this->_ressourcesMutex);
  this->_ressources.changeLife(static_cast<int>(amount) * -1);
}

void	Game::AElement::addEffect(const Game::Effect *effect) {
  ScopeLock s(this->_effectsMutex);
  this->_temporaryEffects.push_back(effect);
}

void	Game::AElement::removeEffect(const Game::Effect *effect) {
  ScopeLock s(this->_effectsMutex);
  this->_temporaryEffects.remove(effect);
}

void	Game::AElement::endAction(void) {
  Logger::getInstance()->log("Game::AElement::endAction called. Nothing was done.", Logger::FATAL);
}

bool	Game::AElement::removeRessources(unsigned int amount, Kernel::ElementRessources::Type type) {
  ScopeLock s(this->_ressourcesMutex);
  if (type != this->_ressources.getRessourceType() || this->_ressources.getRessource() < amount) {
    return (false);
  }
  this->_ressources.changeRessource(-1 * amount);
  return (true);
}

void	Game::AElement::setCapacityAutomatic(const Kernel::Serial &capacity, bool automatic) {
  ScopeLock s(this->_elementMutex);
  if (this->_capacities[capacity]) {
    this->_capacities[capacity]->setAutomatic(automatic);
  }
}

unsigned int	Game::AElement::getUIntFromData(void *addr) const {
  return (::Game::ABase::getUIntFromData(addr));
}

double	Game::AElement::getDoubleFromData(void *addr) const {
  return (::Game::ABase::getDoubleFromData(addr));
}

void	Game::AElement::setLife(unsigned int amount) {
  ScopeLock s(this->_ressourcesMutex);
  this->_ressources.setLife(amount);
}

void	Game::AElement::setRessources(unsigned int amount) {
  ScopeLock s(this->_ressourcesMutex);
  this->_ressources.setRessources(amount);
}

const std::map<Kernel::Serial, Game::Capacity *>	Game::AElement::getCapacities(void) const {
  return (this->_capacities);
}

void	Game::AElement::_endAction(void) {
  Logger::getInstance()->log("Game::AElement::_endAction called. Nothing was done.", Logger::FATAL);
}
