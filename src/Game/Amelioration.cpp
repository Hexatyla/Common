//
// Amelioration.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 17:36:27 2014 geoffrey bauduin
// Last update Wed Feb 12 17:19:22 2014 geoffrey bauduin
//

#include	"Game/Amelioration.hpp"

Game::Amelioration::Amelioration(void):
  HasSerial(), HasInfos(),
  _owner("") {

}

Game::Amelioration::~Amelioration(void) {}

void	Game::Amelioration::init(const Kernel::Serial &serial, const Kernel::Serial &owner) {
  HasSerial::init(serial);
  HasInfos::init(serial, Game::AMELIORATION);
  this->_owner = owner;
}

const Kernel::Serial &Game::Amelioration::appliesTo(void) const {
  return (this->_owner);
}

void	Game::Amelioration::destroy(void) {
  HasSerial::destroy();
  HasInfos::destroy();
}
