//
// CapacityList.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Thu Jan 16 17:41:12 2014 geoffrey bauduin
// Last update Fri Mar 14 16:14:46 2014 geoffrey bauduin
//

#include	"Kernel/CapacityList.hpp"

Kernel::CapacityList::CapacityList(void):
  list() {

}

Kernel::CapacityList::~CapacityList(void) {}

void	Kernel::CapacityList::destroy(void) {
  this->list.assign(0, "");
}

void	Kernel::CapacityList::init(void) {

}
