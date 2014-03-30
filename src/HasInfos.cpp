//
// HasInfos.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Wed Jan 15 14:22:47 2014 geoffrey bauduin
// Last update Wed Mar  5 18:12:53 2014 geoffrey bauduin
//

#include	<cstddef>
#include	"HasInfos.hpp"
#include	"Kernel/Manager.hpp"

const std::map<Game::Type, int> HasInfos::_masks(HasInfos::initMasks());

const std::map<Game::Type, int> HasInfos::initMasks(void) {
  std::map<Game::Type, int> masks;
  masks[Game::CAPACITY] = DATA | TIMER | COST | CAPACITYDATA;
  masks[Game::EFFECT] = DATA | TIMER | CAPACITYDATA | EFFECT;
  masks[Game::BUILDING] = DATA | TIMER | COST | BUILDINGDATA;
  masks[Game::AMELIORATION] = DATA | TIMER | COST;
  masks[Game::UNIT] = DATA | TIMER | COST;
  masks[Game::HERO] = DATA | TIMER | COST;
  masks[Game::PROJECTILE] = DATA | TIMER | COST;
  masks[Game::OBJECT] = NONE;
  masks[Game::RESSSPOT] = DATA;
  return (masks);
}

HasInfos::HasInfos(void):
  _infos({NULL, NULL, NULL, NULL, NULL, NULL}) {

}

HasInfos::~HasInfos(void) {}

void	HasInfos::init(const Kernel::Serial &serial, Game::Type type) {
  this->_infos.data = NULL;
  this->_infos.cost = NULL;
  this->_infos.timer = NULL;
  this->_infos.capacity = NULL;
  this->_infos.building = NULL;
  if (this->_masks.at(type) & DATA) {
    this->_infos.data = Kernel::Manager::getInstance()->getData(serial);
  }
  if (this->_masks.at(type) & COST) {
    this->_infos.cost = Kernel::Manager::getInstance()->getCost(serial);
  }
  if (this->_masks.at(type) & TIMER) {
    this->_infos.timer = Kernel::Manager::getInstance()->getTimer(serial);
  }
  if (this->_masks.at(type) & CAPACITYDATA) {
    this->_infos.capacity = Kernel::Manager::getInstance()->getCapacityData(serial);
  }
  if (this->_masks.at(type) & BUILDINGDATA) {
    this->_infos.building = Kernel::Manager::getInstance()->getBuildingData(serial);
  }
  if (this->_masks.at(type) & EFFECT) {
    this->_infos.effect = Kernel::Manager::getInstance()->getEffect(serial);
  }
}

void	HasInfos::destroy(void) {

}

const HasInfos::infos &HasInfos::getInfos(void) const {
  return (this->_infos);
}
