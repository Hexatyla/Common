//
// Race.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 18:46:33 2014 geoffrey bauduin
// Last update Mon Mar 24 17:18:02 2014 geoffrey bauduin
//

#include	<algorithm>
#include	"Game/Race.hpp"
#include	"get.hpp"
#include	"Algo/MD5.hpp"
#include	"Kernel/Manager.hpp"
#include	"Logger.hpp"

Game::Race::Race(void):
  HasSerial(),
  _ameliorations(), _buildings(), _units(), _heroes(),
  _vUnits(), _vBuildings(), _vHeroes(), _vAmeliorations(),
  _name(), _maps() {
  this->_maps.push_back(&this->_ameliorations);
  this->_maps.push_back(&this->_buildings);
  this->_maps.push_back(&this->_units);
  this->_maps.push_back(&this->_heroes);
}

Game::Race::~Race(void) {}

void	Game::Race::init(const std::string &name, const Kernel::Serial &serial) {
  HasSerial::init(serial);
  this->_name = name;
}

bool	Game::Race::hasUnitNamed(const std::string &name) const {
  for (auto it : this->_vUnits) {
    const Kernel::Data *data = Kernel::Manager::getInstance()->getData(it);
    if (data && data->name == name) {
      return (true);
    }
  }
  return (false);
}

void	Game::Race::refreshSerial(void) {
  std::string concat = this->_name;
  for (auto map : this->_maps) {
    for (auto it : *map) {
      concat += it.first;
    }
  }
  this->_serial = Algo::MD5::getInstance()->digest(concat);
}

void	Game::Race::destroy(void) {
  HasSerial::destroy();
  for (auto map : this->_maps) {
    for (auto it : *map) {
      //Factory::Game::Requirements::remove(it);
      (void) it;
    }
  }
  this->_ameliorations.clear();
  this->_buildings.clear();
  this->_units.clear();
  this->_heroes.clear();
  this->_vUnits.assign(0, "");
  this->_vBuildings.assign(0, "");
  this->_vHeroes.assign(0, "");
  this->_vAmeliorations.assign(0, "");
}

void	Game::Race::addBuilding(const Kernel::Serial &serial, Game::Requirements *requirements) {
  this->_buildings[serial] = requirements;
  if (!this->hasBuilding(serial)) {
    this->_vBuildings.push_back(serial);
  }
}

void	Game::Race::addUnit(const Kernel::Serial &serial, Game::Requirements *requirements) {
  this->_units[serial] = requirements;
  if (!this->hasUnit(serial)) {
    this->_vUnits.push_back(serial);
  }
}

void	Game::Race::addHero(const Kernel::Serial &serial, Game::Requirements *requirements) {
  this->_heroes[serial] = requirements;
  if (!this->hasHero(serial)) {
    this->_vHeroes.push_back(serial);
  }
}

void	Game::Race::addAmelioration(const Kernel::Serial &serial, Game::Requirements *requirements) {
  this->_ameliorations[serial] = requirements;
  if (!this->hasAmelioration(serial)) {
    this->_vAmeliorations.push_back(serial);
  }
}

const std::string &Game::Race::getName(void) const {
  return (this->_name);
}

bool	Game::Race::find(const std::vector<Kernel::Serial> &c, const Kernel::Serial &serial) const {
  return (std::find(c.begin(), c.end(), serial) != c.end());
}

bool	Game::Race::hasUnit(const Kernel::Serial &serial) const {
  return (this->find(this->_vUnits, serial));
}

bool	Game::Race::hasBuilding(const Kernel::Serial &serial) const {
  return (this->find(this->_vBuildings, serial));
}

bool	Game::Race::hasHero(const Kernel::Serial &serial) const {
  return (this->find(this->_vHeroes, serial));
}

bool	Game::Race::hasAmelioration(const Kernel::Serial &serial) const {
  return (this->find(this->_vAmeliorations, serial));
}

const Game::Requirements *Game::Race::getUnitRequirements(const Kernel::Serial &serial) const {
  return (get(serial, this->_units));
}

const Game::Requirements *Game::Race::getBuildingRequirements(const Kernel::Serial &serial) const {
  return (get(serial, this->_buildings));
}

const Game::Requirements *Game::Race::getHeroRequirements(const Kernel::Serial &serial) const {
  return (get(serial, this->_heroes));
}

const Game::Requirements *Game::Race::getAmeliorationRequirements(const Kernel::Serial &serial) const {
  return (get(serial, this->_ameliorations));
}

const std::vector<Kernel::Serial>	&Game::Race::getUnits(void) const {
  return (this->_vUnits);
}

const std::vector<Kernel::Serial>	&Game::Race::getBuildings(void) const {
  return (this->_vBuildings);
}

const std::vector<Kernel::Serial>	&Game::Race::getHeroes(void) const {
  return (this->_vHeroes);
}

const std::vector<Kernel::Serial>	&Game::Race::getAmeliorations(void) const {
  return (this->_vAmeliorations);
}


bool	Game::Race::hasItem(const Kernel::Serial &serial, ::Game::Type type) const {
  switch (type) {
  case Game::UNIT:
    return (this->hasUnit(serial));
  case Game::BUILDING:
    return (this->hasBuilding(serial));
  case Game::HERO:
    return (this->hasHero(serial));
  case Game::AMELIORATION:
    return (this->hasAmelioration(serial));
  default:
    break;
  }
  return (false);
}

void	Game::Race::setRequirements(const Kernel::Serial &serial, Game::Requirements *requirements) {
  const Kernel::Data *data = Kernel::Manager::getInstance()->getData(serial);
  if (!data) {
    return ;
  }
  switch (data->type) {
  case Game::UNIT:
    this->addUnit(serial, requirements);
    break;
  case Game::AMELIORATION:
    this->addAmelioration(serial, requirements);
    break;
  case Game::HERO:
    this->addHero(serial, requirements);
    break;
  case Game::BUILDING:
    this->addBuilding(serial, requirements);
    break;
  default:
    break;
  }
}

void	Game::Race::dump(void) const {
  std::vector<std::string> s;
  s.push_back("Ameliorations :");
  s.push_back("Buildings :");
  s.push_back("Units :");
  s.push_back("Heroes :");
  std::vector<std::string>::iterator _it = s.begin();
  Logger::getInstance()->logf("Race -%s- [%s]", Logger::DEBUG, &this->_name, &this->_serial);
  Logger::getInstance()->addDecalage();
  for (auto d : this->_maps) {
    Logger::getInstance()->log(*_it, Logger::DEBUG);
    Logger::getInstance()->addDecalage();
    for (auto it : *d) {
      const Kernel::Data *data = Kernel::Manager::getInstance()->getData(it.first);
      Logger::getInstance()->logf("-%s- [%s] :", Logger::DEBUG, &data->name, &it.first);
      Logger::getInstance()->addDecalage();
      std::string a = "";
      for (auto it : data->ameliorations) {
	if (a != "") {
	  a += ", ";
	}
	a += it;
      }
      Logger::getInstance()->logf("Ameliorations - %s", Logger::DEBUG, &a);
      it.second->dump();
      Logger::getInstance()->removeDecalage();
    }
    Logger::getInstance()->removeDecalage();
    ++_it;
  }
  Logger::getInstance()->removeDecalage();
}
