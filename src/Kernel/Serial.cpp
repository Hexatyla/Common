//
// Serial.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Thu Jan 16 17:56:38 2014 geoffrey bauduin
// Last update Tue Mar 25 17:32:31 2014 geoffrey bauduin
//

#include	<string.h>
#include	"Algo/MD5.hpp"
#include	"Kernel/Serial.hpp"

const Kernel::Serial	Kernel::create_serial(const std::string &data) {
  return (Algo::MD5::getInstance()->digest(data));
}

void	Kernel::assign_serial(char *serial, const std::string &d) {
  memset(serial, 0, 33);
  strncpy(serial, d.c_str(), 32);
}

const Kernel::Serial	Kernel::get_serial(const char *string) {
  Kernel::Serial serial;
  serial.assign(string, 32);
  return (serial);
}

// Kernel::Serial::Serial(const char *string) {
//   this->assign(string, 32);
// }

// Kernel::Serial::Serial(void) {

// }

// Kernel::Serial::~Serial(void) {}

// Kernel::Serial	&Kernel::Serial::operator=(const char *string) {
//   this->assign(string, 32);
// }
