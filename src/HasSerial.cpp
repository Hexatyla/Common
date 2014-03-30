//
// HasSerial.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Jan 14 15:44:41 2014 geoffrey bauduin
// Last update Wed Feb 12 17:15:08 2014 geoffrey bauduin
//

#include	"HasSerial.hpp"

HasSerial::HasSerial(void):
  _serial("") {

}

HasSerial::~HasSerial(void) {}

void	HasSerial::init(const Kernel::Serial &serial) {
  this->_serial = serial;
}

const Kernel::Serial	&HasSerial::serial(void) const {
  return (this->_serial);
}

void	HasSerial::destroy(void) {}
