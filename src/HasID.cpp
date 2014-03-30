//
// HasID.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Mon Jan 20 10:46:09 2014 geoffrey bauduin
// Last update Wed Feb 12 17:15:56 2014 geoffrey bauduin
//

#include	"HasID.hpp"

HasID::HasID(void):
  _id(0) {
}

HasID::~HasID(void) {}

void	HasID::init(Kernel::ID::id_t id) {
  this->_id = id;
}

unsigned int	HasID::getID(void) const {
  return (this->_id);
}

void	HasID::destroy(void) {

}
