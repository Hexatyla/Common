//
// CapacityData.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 17 15:03:48 2014 geoffrey bauduin
// Last update Fri Mar 14 16:11:40 2014 geoffrey bauduin
//

#include	"Kernel/CapacityData.hpp"

Kernel::CapacityData::CapacityData(void):
  projectiles(), effects(), canAuto(false) {

}

Kernel::CapacityData::~CapacityData(void) {}

void	Kernel::CapacityData::init(bool canAuto, bool isAuto, bool passive) {
  this->canAuto = canAuto;
  this->isAuto = isAuto;
  this->passive = passive;
}

void	Kernel::CapacityData::destroy(void) {
  this->projectiles.assign(0, "");
  this->effects.assign(0, "");
}
