//
// Effect.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Mon Feb  3 14:05:10 2014 geoffrey bauduin
// Last update Fri Mar 14 16:15:16 2014 geoffrey bauduin
//

#include	"Kernel/Effect.hpp"

Kernel::Effect::Effect(void):
  type(NONE), targetSide(ALL), targetType(Game::NONE), effects() {

}

Kernel::Effect::~Effect(void) {}

void	Kernel::Effect::init(Kernel::Effect::Type type_, Kernel::Effect::TargetSide targetSide_, Game::Type targetType_) {
  this->type = type_;
  this->targetSide = targetSide_;
  this->targetType = targetType_;
}

void	Kernel::Effect::destroy(void) {
  this->effects.assign(0, "");
}
