//
// Player.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 18:52:18 2014 geoffrey bauduin
// Last update Tue Mar 25 17:16:43 2014 geoffrey bauduin
//

#include	<algorithm>
#include	<cstddef>
#include	"Game/Player.hpp"
#include	"Game/Team.hpp"
#include	"Logger.hpp"
#include	"Threading/ScopeLock.hpp"
#include	"Factory/Game.hpp"

Game::Player::Player(void):
  HasID(),
  _dataMutex(new Mutex), _ressourcesMutex(new Mutex), _queuesMutex(new Mutex),
  _ameliorations(), _nbrUnits(0), _nbrBuildings(0), _nbrHeroes(0), _race(NULL),
  _ressources(), _team(NULL),
  _productionQueues(), _buildings() {

}

Game::Player::~Player(void) {
  delete this->_dataMutex;
  delete this->_ressourcesMutex;
  delete this->_queuesMutex;
}

void	Game::Player::destroy(void) {
  HasID::destroy();
  for (auto it : this->_productionQueues) {
    Factory::Game::ProductionQueue::remove(it.second);
  }
  this->_productionQueues.clear();
  for (auto it : this->_ameliorations) {
    for (auto amelio : it.second) {
      Factory::Game::Amelioration::remove(amelio);
    }
  }
  this->_ameliorations.clear();
  this->_ressources.destroy();
  this->_buildings.clear();
}

void	Game::Player::init(Kernel::ID::id_t id, const Game::Race *race, const Game::Team *team) {
  HasID::init(id);
  this->_race = race;
  this->_ameliorations.clear();
  this->_nbrUnits = 0;
  this->_nbrBuildings = 0;
  this->_nbrHeroes = 0;
  this->_ressources.init(0, 0, 0);
  this->_team = team;
  Game::ProductionQueue *queue;
  Logger::getInstance()->logf("Creating queues for player %d", Logger::DEBUG, id);
  for (auto it : this->_race->getUnits()) {
    Logger::getInstance()->logf("Creating queue for %s", Logger::DEBUG, &it);
    queue = Factory::Game::ProductionQueue::create();
    this->_productionQueues[it] = queue;
    this->_ameliorations[it] = std::vector<Game::Amelioration *>();
  }
  for (auto it : this->_race->getBuildings()) {
    Logger::getInstance()->logf("Creating queue for %s", Logger::DEBUG, &it);
    queue = Factory::Game::ProductionQueue::create();
    this->_productionQueues[it] = queue;
    this->_ameliorations[it] = std::vector<Game::Amelioration *>();
  }
  for (auto it : this->_race->getHeroes()) {
    Logger::getInstance()->logf("Creating queue for %s", Logger::DEBUG, &it);
    queue = Factory::Game::ProductionQueue::create();
    this->_productionQueues[it] = queue;
    this->_ameliorations[it] = std::vector<Game::Amelioration *>();
  }
  Logger::getInstance()->log("");
}

const Game::Team	*Game::Player::getTeam(void) const {
  return (this->_team);
}

void	Game::Player::setRessources(Game::Ressources::Type type, unsigned int amount) {
  this->_ressources.set(type, amount);
}

const std::vector<Game::Amelioration *>	Game::Player::getAmeliorations(void) const {
  ScopeLock s(this->_dataMutex);
  std::vector<Game::Amelioration *> v;
  for (auto it : this->_ameliorations) {
    for (auto amelio : it.second) {
      v.push_back(amelio);
    }
  }
  return (v);
}

bool	Game::Player::hasAmelioration(const Kernel::Serial &serial) const {
  ScopeLock s(this->_dataMutex);
  for (auto it : this->_ameliorations) {
    for (auto amelio : it.second) {
      if (amelio->serial() == serial) {
	return (true);
      }
    }
  }
  return (false);
}

bool	Game::Player::hasBuilding(const Kernel::Serial &serial) const {
  ScopeLock s(this->_dataMutex);
  return (std::find(this->_buildings.begin(), this->_buildings.end(), serial) != this->_buildings.end());
}

void	Game::Player::addBuilding(const Kernel::Serial &serial) {
  ScopeLock s(this->_dataMutex);
  this->_buildings.push_back(serial);
}

void	Game::Player::removeBuilding(const Kernel::Serial &serial) {
  ScopeLock s(this->_dataMutex);
  this->_buildings.remove(serial);
}

const std::vector<Game::Amelioration *>	&Game::Player::getAmeliorations(const Kernel::Serial &serial) const {
  ScopeLock s(this->_dataMutex);
  return (this->_ameliorations.at(serial));
}

const Game::Race	*Game::Player::getRace(void) const {
  return (this->_race);
}

bool	Game::Player::hasAmelioration(const Kernel::Serial &type, const Kernel::Serial &amelioration) const {
  ScopeLock s(this->_dataMutex);
  if (this->_ameliorations.find(type) != this->_ameliorations.end()) {
    for (auto it : this->_ameliorations.at(type)) {
      if (it->serial() == amelioration) {
	return (true);
      }
    }
  }
  return (false);
}

bool	Game::Player::isInQueue(const Kernel::Serial &type, const Kernel::Serial &amelioration) const {
  ScopeLock s(this->_queuesMutex);
  if (this->_productionQueues.find(type) != this->_productionQueues.end()) {
    return (this->_productionQueues.at(type)->contains(amelioration));
  }
  return (false);
}

void	Game::Player::setTeam(const Game::Team *team) {
  ScopeLock s(this->_dataMutex);
  this->_team = team;
}

bool	Game::Player::isAlliedWith(const Game::Player *player) const {
  return (this->_team->isInTeam(player));
}

void	Game::Player::addUnit(unsigned int amount) {
  ScopeLock s(this->_dataMutex);
  this->_nbrUnits += amount;
}

void	Game::Player::removeUnit(unsigned int amount) {
  ScopeLock s(this->_dataMutex);
  this->_nbrUnits -= amount;
}

void	Game::Player::addHero(unsigned int amount) {
  ScopeLock s(this->_dataMutex);
  this->_nbrHeroes += amount;
}

void	Game::Player::removeHero(unsigned int amount) {
  ScopeLock s(this->_dataMutex);
  this->_nbrHeroes -= amount;
}

void	Game::Player::addBuilding(unsigned int amount) {
  ScopeLock s(this->_dataMutex);
  this->_nbrBuildings += amount;
}

void	Game::Player::removeBuilding(unsigned int amount) {
  ScopeLock s(this->_dataMutex);
  this->_nbrBuildings -= amount;
}

unsigned int	Game::Player::getNbrUnits(void) const {
  return (this->_nbrUnits);
}

unsigned int	Game::Player::getNbrHeroes(void) const {
  return (this->_nbrHeroes);
}

unsigned int	Game::Player::getNbrBuildings(void) const {
  return (this->_nbrBuildings);
}

void	Game::Player::addRessources(const Game::Ressources &rhs) {
  ScopeLock s(this->_ressourcesMutex);
  this->_ressources += rhs;
}

void	Game::Player::addRessources(Game::Ressources::Type type, unsigned int amount) {
  ScopeLock s(this->_ressourcesMutex);
  this->_ressources.add(type, static_cast<int>(amount));
}

void	Game::Player::removeRessources(const Game::Ressources &rhs) {
  ScopeLock s(this->_ressourcesMutex);
  this->_ressources -= rhs;
}

void	Game::Player::removeRessources(Game::Ressources::Type type, unsigned int amount) {
  ScopeLock s(this->_ressourcesMutex);
  this->_ressources.add(type, -1 * static_cast<int>(amount));
}

const Game::Ressources &Game::Player::getRessources(void) const {
  return (this->_ressources);
}

unsigned int	Game::Player::getRessources(Game::Ressources::Type type) const {
  ScopeLock s(this->_ressourcesMutex);
  return (this->_ressources.get(type));
}

bool	Game::Player::hasEnoughRessources(const Game::Ressources &ressources) const {
  ScopeLock s(this->_ressourcesMutex);
  return (this->_ressources.hasEnough(ressources));
}

void	Game::Player::addToQueue(const Kernel::Serial &type, const Kernel::Serial &serial) {
  ScopeLock s(this->_queuesMutex);
  if (!this->_productionQueues[type]) {
    Logger::getInstance()->logf("NO QUEUE FOR TYPE %s", Logger::FATAL, &type);
    this->_productionQueues[type] = Factory::Game::ProductionQueue::create();
  }
  this->_productionQueues[type]->push(serial);
}

void	Game::Player::insertInQueue(const Kernel::Serial &type, const Kernel::Serial &serial, unsigned int pos) {
  ScopeLock s(this->_queuesMutex);
  if (!this->_productionQueues[type]) {
    Logger::getInstance()->logf("NO QUEUE FOR TYPE %s", Logger::FATAL, &type);
    this->_productionQueues[type] = Factory::Game::ProductionQueue::create();
  }
  this->_productionQueues[type]->insert(serial, pos);
}

bool	Game::Player::removeFromQueue(const Kernel::Serial &type, const Kernel::Serial &serial) {
  ScopeLock s(this->_queuesMutex);
  if (!this->_productionQueues[type]) {
    Logger::getInstance()->logf("NO QUEUE FOR TYPE %s", Logger::FATAL, &type);
    this->_productionQueues[type] = Factory::Game::ProductionQueue::create();
  }
  return (this->_productionQueues[type]->remove(serial));
}

const Kernel::Serial	Game::Player::popQueue(const Kernel::Serial &type) {
  ScopeLock s(this->_queuesMutex);
  if (this->_productionQueues[type]) {
    return (this->_productionQueues[type]->pop());
  }
  return (Kernel::Serial(""));
}

const Kernel::Serial	&Game::Player::frontQueue(const Kernel::Serial &type) const {
  ScopeLock s(this->_queuesMutex);
  return (this->_productionQueues.at(type)->front());
}

const Kernel::Serial	&Game::Player::backQueue(const Kernel::Serial &type) const {
  ScopeLock s(this->_queuesMutex);
  return (this->_productionQueues.at(type)->back());
}

bool	Game::Player::hasLost(void) const {
  return (this->_nbrUnits == 0 && this->_nbrHeroes == 0 && this->_nbrBuildings == 0);
}

void	Game::Player::addAmelioration(const Kernel::Serial &type, const Kernel::Serial &amelioration) {
  for (auto it : this->_ameliorations[type]) {
    if (it->serial() == amelioration) {
      return ;
    }
  }
  this->_ameliorations[type].push_back(Factory::Game::Amelioration::create(amelioration, type));
}
