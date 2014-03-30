//
// Cost.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sun Jan 12 14:00:27 2014 geoffrey bauduin
// Last update Wed Feb 12 17:25:32 2014 geoffrey bauduin
//

#include	"Kernel/Cost.hpp"

Kernel::Cost::Cost(void):
  ressources(), personnalRessource() {
}

Kernel::Cost::~Cost(void) {}

void	Kernel::Cost::init(unsigned int gold, unsigned int wood, unsigned int food,
			   Kernel::ElementRessources::Type type, unsigned int value,
			   unsigned int life) {
  this->ressources.init(gold, wood, food);
  this->personnalRessource.init(life, type, value, 0, 0);
}

void	Kernel::Cost::destroy(void) {
  this->ressources.destroy();
  this->personnalRessource.destroy();
}
