//
// BuildingData.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 17 16:29:57 2014 geoffrey bauduin
// Last update Fri Mar 14 16:14:26 2014 geoffrey bauduin
//

#include	"Kernel/BuildingData.hpp"

Kernel::BuildingData::BuildingData(void):
  units() {

}

Kernel::BuildingData::~BuildingData(void) {}

void	Kernel::BuildingData::init(void) {
}

void	Kernel::BuildingData::destroy(void) {
  this->units.assign(0, "");
}
