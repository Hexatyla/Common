//
// Factory.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 15:55:10 2014 geoffrey bauduin
// Last update Tue Mar 11 15:22:27 2014 geoffrey bauduin
//

#include	<vector>
#include	<cstddef>
#include	"Factory/Kernel.hpp"
#include	"Factory/Pool.hpp"

static Pool< ::Kernel::Data>			*poolKernelData;
static Pool< ::Kernel::Cost>			*poolKernelCost;
static Pool< ::Kernel::Time>			*poolKernelTime;
static Pool< ::Kernel::CapacityList>		*poolKernelCapacityList;
static Pool< ::Kernel::CapacityData>		*poolKernelCapacityData;
static Pool< ::Kernel::BuildingData>		*poolKernelBuildingData;
static Pool< ::Kernel::Effect>			*poolKernelEffect;

void	Factory::Kernel::init(void) {
  poolKernelData = new Pool< ::Kernel::Data>(1000, 100, "Kernel::Data");
  poolKernelCost = new Pool< ::Kernel::Cost>(1000, 100, "Kernel::Cost");
  poolKernelTime = new Pool< ::Kernel::Time>(1000, 100, "Kernel::Time");
  poolKernelCapacityList = new Pool< ::Kernel::CapacityList>(1000, 100, "Kernel::CapacityList");
  poolKernelCapacityData = new Pool< ::Kernel::CapacityData>(1000, 100, "Kernel::CapacityData");
  poolKernelBuildingData = new Pool< ::Kernel::BuildingData>(1000, 100, "Kernel::BuildingData");
  poolKernelEffect = new Pool< ::Kernel::Effect>(1000, 100, "Kernel::Effect");
}

void	Factory::Kernel::end(void) {
  delete poolKernelData;
  delete poolKernelCost;
  delete poolKernelTime;
  delete poolKernelCapacityList;
  delete poolKernelCapacityData;
  delete poolKernelBuildingData;
  delete poolKernelEffect;
}

::Kernel::Data	*Factory::Kernel::Data::create(Game::Type type, 
					       const std::string &name, const std::string &serial, unsigned int attack,
					       unsigned int defense, unsigned int hpRegen, unsigned int speed,
					       double critChance, unsigned int maxHP, double hitbox, double attackRange,
					       int passthrough, ::Kernel::ElementRessources::Type typeRessources,
					       unsigned int maxRessources, unsigned int ressourcesRegen, double sightD, double sightN) {
  ::Kernel::Data *item = poolKernelData->get();
  item->init(type, name, serial, attack, defense, hpRegen, speed, critChance, maxHP, hitbox, attackRange, passthrough, typeRessources, maxRessources, ressourcesRegen, sightD, sightN);
  return (item);
}

void	Factory::Kernel::Data::remove(::Kernel::Data *data) {
  data->destroy();
  poolKernelData->push(data);
}

::Kernel::Cost	*Factory::Kernel::Cost::create(unsigned int r1, unsigned int r2, unsigned int r3,
						       ::Kernel::ElementRessources::Type type, unsigned int r4, unsigned int r5) {
  ::Kernel::Cost *item = poolKernelCost->get();
  item->init(r1, r2, r3, type, r4, r5);
  return (item);
}

void	Factory::Kernel::Cost::remove(::Kernel::Cost *item) {
  item->destroy();
  poolKernelCost->push(item);
}

::Kernel::Time	*Factory::Kernel::Time::create(double canalisation, double construction, double duration, double cd, ::Kernel::Time::Canalisation when) {
  ::Kernel::Time *item = poolKernelTime->get();
  item->init(canalisation, construction, duration, cd, when);
  return (item);
}

void	Factory::Kernel::Time::remove(::Kernel::Time *item) {
  item->destroy();
  poolKernelTime->push(item);
}

::Kernel::CapacityList	*Factory::Kernel::CapacityList::create(void) {
  ::Kernel::CapacityList *item = poolKernelCapacityList->get();
  item->init();
  return (item);
}

void	Factory::Kernel::CapacityList::remove(::Kernel::CapacityList *item) {
  item->destroy();
  poolKernelCapacityList->push(item);
}

::Kernel::CapacityData	*Factory::Kernel::CapacityData::create(bool cA, bool iA, bool passive) {
  ::Kernel::CapacityData *item = poolKernelCapacityData->get();
  item->init(cA, iA, passive);
  return (item);
}

void	Factory::Kernel::CapacityData::remove(::Kernel::CapacityData *item) {
  item->destroy();
  poolKernelCapacityData->push(item);
}

::Kernel::BuildingData	*Factory::Kernel::BuildingData::create(void) {
  ::Kernel::BuildingData *item = poolKernelBuildingData->get();
  item->init();
  return (item);
}

void	Factory::Kernel::BuildingData::remove(::Kernel::BuildingData *item) {
  item->destroy();
  poolKernelBuildingData->push(item);
}

::Kernel::Effect	*Factory::Kernel::Effect::create(::Kernel::Effect::Type type, ::Kernel::Effect::TargetSide targetSide, ::Game::Type targetType) {
  ::Kernel::Effect *item = poolKernelEffect->get();
  item->init(type, targetSide, targetType);
  return (item);
}

void	Factory::Kernel::Effect::remove(::Kernel::Effect *item) {
  item->destroy();
  poolKernelEffect->push(item);
}
