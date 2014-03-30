//
// Requirements.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 18:54:55 2014 geoffrey bauduin
// Last update Tue Mar 25 13:41:55 2014 geoffrey bauduin
//

#include	"Game/Requirements.hpp"
#include	"Logger.hpp"
#include	"Kernel/Manager.hpp"
#include	"Game/Player.hpp"
#include	"Threading/ScopeLock.hpp"

Game::Requirements::Requirements(void):
  _mutex(new Mutex), _buildings(), _ameliorations() {}

Game::Requirements::~Requirements(void) {
  delete this->_mutex;
}

void	Game::Requirements::init(void) {

}

void	Game::Requirements::destroy(void) {
  this->_buildings.assign(0, "");
  this->_ameliorations.assign(0, "");
}

void	Game::Requirements::addBuilding(const Kernel::Serial &serial) {
  ScopeLock s(this->_mutex);
  this->_buildings.push_back(serial);
}

void	Game::Requirements::addAmelioration(const Kernel::Serial &serial) {
  ScopeLock s(this->_mutex);
  this->_ameliorations.push_back(serial);
}

bool	Game::Requirements::fullfilledByPlayer(const Game::Player *player) const {
  return (true);
  ScopeLock s(this->_mutex);
  for (auto it : this->_ameliorations) {
    if (player->hasAmelioration(it) == false) {
      return (false);
    }
  }
  for (auto it : this->_buildings) {
    if (player->hasBuilding(it) == false) {
      return (false);
    }
  }
  return (true);
}

const std::vector<Kernel::Serial>	&Game::Requirements::getBuildings(void) const {
  return (this->_buildings);
}

const std::vector<Kernel::Serial>	&Game::Requirements::getAmeliorations(void) const {
  return (this->_ameliorations);
}

const std::map<Kernel::Serial, bool>	Game::Requirements::getFullfilledData(const Game::Player *player) const {
  std::map<Kernel::Serial, bool> fullfilled;
  ScopeLock s(this->_mutex);
  for (auto it : this->_ameliorations) {
    fullfilled[it] = player->hasAmelioration(it);
  }
  for (auto it : this->_buildings) {
    fullfilled[it] = player->hasBuilding(it);
  }
  return (fullfilled);
}

void	Game::Requirements::dump(void) const {
  Logger::getInstance()->log("Requirements -", Logger::DEBUG);
  Logger::getInstance()->addDecalage();
  std::string b = "";
  for (auto it : this->_buildings) {
    const Kernel::Data *data = Kernel::Manager::getInstance()->getData(it);
    if (b != "") {
      b += ", ";
    }
    b += data->name;
  }
  std::string a = "";
  for (auto it : this->_ameliorations) {
    const Kernel::Data *data = Kernel::Manager::getInstance()->getData(it);
    if (a != "") {
      a += ", ";
    }
    a += data->name;
  }
  Logger::getInstance()->logf("Buildings : %s", Logger::DEBUG, &b);
  Logger::getInstance()->logf("Ameliorations : %s", Logger::DEBUG, &a);
  Logger::getInstance()->removeDecalage();
}
