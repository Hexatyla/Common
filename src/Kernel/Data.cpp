//
// Data.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sun Jan 12 13:54:41 2014 geoffrey bauduin
// Last update Thu Mar 13 15:00:44 2014 geoffrey bauduin
//

#include	"Kernel/Data.hpp"

Kernel::Data::Data(void):
  attack(0), defense(0), hpRegen(0), speed(0), critChance(0.0), maxHP(0),
  name(""), serial(""), hitbox(0.0), attackRange(0.0), passthrough(0), daySight(0.0), nightSight(0.0),
  ameliorations() {

}

Kernel::Data::~Data(void) {}

void	Kernel::Data::init(Game::Type type, const std::string &name, const std::string &serial, unsigned int attack,
			   unsigned int defense, unsigned int hpRegen, unsigned int speed,
			   double critChance, unsigned int maxHP, double hitbox, double attackRange,
			   int passthrough, Kernel::ElementRessources::Type typeRessources,
			   unsigned int maxRessources, unsigned int ressourcesRegen, double sightD,
			   double sightN) {
  this->type = type;
  this->name = name;
  this->serial = serial;
  this->attack = attack;
  this->defense = defense;
  this->hpRegen = hpRegen;
  this->speed = speed;
  this->critChance = critChance;
  this->maxHP = maxHP;
  this->hitbox = hitbox;
  this->passthrough = passthrough;
  this->typeRessources = typeRessources;
  this->maxRessources = maxRessources;
  this->ressourcesRegen = ressourcesRegen;
  this->daySight = sightD;
  this->nightSight = sightN;
  this->attackRange = attackRange;
}

void	Kernel::Data::destroy(void) {

}
