//
// Time.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sun Jan 12 14:27:26 2014 geoffrey bauduin
// Last update Wed Feb 12 17:24:51 2014 geoffrey bauduin
//

#include	"Kernel/Time.hpp"

Kernel::Time::Time(void):
  when(NONE), canalisation(0.0), creation(0.0), duration(0.0), cooldown(0.0) {

}

Kernel::Time::~Time(void) {}

void	Kernel::Time::init(double canalisation, double creation, double duration, double cd, Kernel::Time::Canalisation when) {
  this->canalisation = canalisation;
  this->creation = creation;
  this->duration = duration;
  this->when = when;
  this->cooldown = cd;
}

void	Kernel::Time::destroy(void) {
  
}
