//
// Manager.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sun Jan 12 14:41:06 2014 geoffrey bauduin
// Last update Tue Mar 25 15:22:32 2014 geoffrey bauduin
//

#include	<cstddef>
#include	<stdexcept>
#include	"Kernel/Manager.hpp"
#include	"Factory/Kernel.hpp"
#include	"Kernel/Config.hpp"
#include	"get.hpp"

Kernel::Manager::Manager(void):
  _datas(), _costs(), _timers(), _capacityList(), _capacityData(), _buildingData(), _effects() {
}

Kernel::Manager::~Manager(void) {
  for (auto it : this->_datas) {
    Factory::Kernel::Data::remove(it.second);
  }
  for (auto it : this->_costs) {
    Factory::Kernel::Cost::remove(it.second);
  }
  for (auto it : this->_timers) {
    Factory::Kernel::Time::remove(it.second);
  }
  for (auto it : this->_capacityList) {
    Factory::Kernel::CapacityList::remove(it.second);
  }
  for (auto it : this->_capacityData) {
    Factory::Kernel::CapacityData::remove(it.second);
  }
  for (auto it : this->_buildingData) {
    Factory::Kernel::BuildingData::remove(it.second);
  }
  for (auto it : this->_effects) {
    Factory::Kernel::Effect::remove(it.second);
  }
}

void	Kernel::Manager::init(void) {
  {
    std::vector<Kernel::Serial> capacities;
    capacities.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::BUILD_CAPACITY));
    capacities.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::CARRY_RESSOURCES_CAPACITY));
    capacities.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::HARVEST_CAPACITY));
    capacities.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::RECOVER_GOLD_CAPACITY));
    capacities.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::RECOVER_WOOD_CAPACITY));
    capacities.push_back(Kernel::Config::getInstance()->getString(Kernel::Config::PATROL_CAPACITY));
#ifndef __SERVER__
    std::vector<std::string> img;
    img.push_back("capacity_build.png");
    img.push_back("capacity_carry.png");
    img.push_back("capacity_harvest.png");
    img.push_back("capacity_deposit_gold.png");
    img.push_back("capacity_deposit_wood.png");
    img.push_back("capacity_patrol.png");
    std::vector<std::string>::iterator itImg = img.begin();
#endif
    for (auto it : capacities) {
      Kernel::Data *data = Factory::Kernel::Data::create(::Game::CAPACITY, it, it, 0, 0, 0, 0, 0.0, 0, 0.0, 0.0, 0,
							 Kernel::ElementRessources::NONE, 0, 0, 0.0, 0.0);
      Kernel::Time *timer = Factory::Kernel::Time::create(0.0, 0.0, 0.0, 0.0);
      Kernel::Cost *cost = Factory::Kernel::Cost::create(0, 0, 0, Kernel::ElementRessources::NONE, 0, 0);
      Kernel::CapacityData *cData = Factory::Kernel::CapacityData::create(false, false, true);
#ifndef __SERVER__
      data->voice = "";
      data->voiceBirth = "";
      data->voiceDie = "";
      data->voiceAttack = "";
      data->icon = *itImg;
      data->model = "";
      ++itImg;
#endif
      this->addData(it, data);
      this->addTimer(it, timer);
      this->addCost(it, cost);
      this->addCapacityData(it, cData);
    }
  }
  {
    const std::string serial = Kernel::Config::getInstance()->getString(Kernel::Config::GOLD_SPOT_SERIAL);
    Kernel::Data *data = Factory::Kernel::Data::create(::Game::RESSSPOT, serial, serial, 0, 0, 0, 0, 0.0, 0, 0.2,
						       0.0, 0, Kernel::ElementRessources::NONE, 0, 0, 0.0, 0.0);
#ifndef __SERVER__
    data->voice = "";
    data->voiceBirth = "";
    data->voiceDie = "";
    data->voiceAttack = "";
    data->icon = "gold_spot.png";
    data->model = "goldmine.mesh";
#endif
    this->addData(serial, data);
  }
  {
    const std::string serial = Kernel::Config::getInstance()->getString(Kernel::Config::WOOD_SPOT_SERIAL);
    Kernel::Data *data = Factory::Kernel::Data::create(::Game::RESSSPOT, serial, serial, 0, 0, 0, 0, 0.0, 0, 0.2,
						       0.0, 0, Kernel::ElementRessources::NONE, 0, 0, 0.0, 0.0);
#ifndef __SERVER__
    data->voice = "";
    data->voiceBirth = "";
    data->voiceDie = "";
    data->voiceAttack = "";
    data->icon = "wood_spot.png";
    data->model = "tree.mesh";
#endif
    this->addData(serial, data);
  }
  {
    std::vector<Kernel::Serial> lvlData;
    lvlData.push_back(LEVEL_1_DATA);
    lvlData.push_back(LEVEL_2_DATA);
    lvlData.push_back(LEVEL_3_DATA);
    lvlData.push_back(LEVEL_4_DATA);
    lvlData.push_back(LEVEL_5_DATA);
    lvlData.push_back(LEVEL_6_DATA);
    lvlData.push_back(LEVEL_7_DATA);
    lvlData.push_back(LEVEL_8_DATA);
    lvlData.push_back(LEVEL_9_DATA);
    lvlData.push_back(LEVEL_10_DATA);
    unsigned int cLvl = 0;
    for (auto it : lvlData) {
      Kernel::Data *data = Factory::Kernel::Data::create(::Game::NONE, it, it, cLvl * 3, cLvl, cLvl, cLvl * 6,
							 cLvl * 0.03, cLvl * 10, 0.0, cLvl * 0.2, 0,
							 Kernel::ElementRessources::NONE, cLvl * 3, cLvl, cLvl * 0.2,
							 cLvl * 0.1);
      this->addData(it, data);
      cLvl++;
    }
  }
}

void	Kernel::Manager::loadRace(const Kernel::Serial &) {}

void	Kernel::Manager::deleteRace(const Game::Race *) {}

const Kernel::Data	*Kernel::Manager::getData(const Kernel::Serial &serial) const {
  return (get(serial, this->_datas));
  //  return (this->_datas.at(serial));
}

void	Kernel::Manager::addData(const Kernel::Serial &serial, Kernel::Data *data) {
  this->_datas[serial] = data;
}

const Kernel::Cost	*Kernel::Manager::getCost(const Kernel::Serial &serial) const {
  return (get(serial, this->_costs));
  //  return (this->_costs.at(serial));
}

void	Kernel::Manager::addCost(const Kernel::Serial &serial, Kernel::Cost *cost) {
  this->_costs[serial] = cost;
}

const Kernel::Time		*Kernel::Manager::getTimer(const Kernel::Serial &serial) const {
  return (get(serial, this->_timers));
  //return (this->_timers.at(serial));
}

void	Kernel::Manager::addTimer(const Kernel::Serial &serial, Kernel::Time *timer) {
  this->_timers[serial] = timer;
}

const Kernel::CapacityList	*Kernel::Manager::getCapacityList(const Kernel::Serial &serial) const {
  return (get(serial, this->_capacityList));
  //return (this->_capacityList.at(serial));
}

void	Kernel::Manager::addCapacityList(const Kernel::Serial &serial, Kernel::CapacityList *list) {
  this->_capacityList[serial] = list;
}

const Kernel::CapacityData	*Kernel::Manager::getCapacityData(const Kernel::Serial &serial) const {
  return (get(serial, this->_capacityData));
  //return (this->_capacityData.at(serial));
}

void	Kernel::Manager::addCapacityData(const Kernel::Serial &serial, Kernel::CapacityData *data) {
  this->_capacityData[serial] = data;
}

const Kernel::BuildingData	*Kernel::Manager::getBuildingData(const Kernel::Serial &serial) const {
  return (get(serial, this->_buildingData));
  //  return (this->_buildingData.at(serial));
}

void	Kernel::Manager::addBuildingData(const Kernel::Serial &serial, Kernel::BuildingData *data) {
  this->_buildingData[serial] = data;
}

void	Kernel::Manager::addEffect(const Kernel::Serial &serial, Kernel::Effect *effect) {
  this->_effects[serial] = effect;
}

const Kernel::Effect	*Kernel::Manager::getEffect(const Kernel::Serial &serial) const {
  return (get(serial, this->_effects));
}
