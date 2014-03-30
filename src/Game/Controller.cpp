//
// Controller.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Mon Feb  3 16:34:14 2014 geoffrey bauduin
// Last update Wed Mar 26 13:57:25 2014 geoffrey bauduin
//

#include	<algorithm>
#include	"Game/Controller.hpp"
#include	"Threading/ScopeLock.hpp"
#include	"Logger.hpp"
#include	"get.hpp"
#include	"Kernel/Manager.hpp"
#include	"Kernel/Config.hpp"
#include	"Factory/Game.hpp"
#include	"Game/CanUseCapacity.hpp"

Game::Controller::Controller(void):
  _mutex(new Mutex), _races(), _hashtab(), _objectTypes() {
  this->_hashtab[Error::NOT_ENOUGH_RESSOURCES] = ::Error::NOT_ENOUGH_RESSOURCES;
  this->_hashtab[Error::NOT_ENOUGH_SELF_RESSOURCES] = ::Error::NOT_ENOUGH_SELF_RESSOURCES;
  this->_hashtab[Error::REQUIREMENTS_NOT_FULLFILLED] = ::Error::REQUIREMENTS_NOT_FULLFILLED;
  this->_hashtab[Error::BUILDING_CANNOT_BUILD_THIS_UNIT] = ::Error::BUILDING_CANNOT_BUILD_THIS_UNIT;
  this->_hashtab[Error::ITEM_NOT_IN_RACE] = ::Error::ITEM_NOT_IN_RACE;
  this->_hashtab[Error::UNKNOWN_ITEM] = ::Error::UNKNOWN_ITEM;
  this->_hashtab[Error::ITEM_IS_NOT_OWNED_BY_PLAYER] = ::Error::ITEM_IS_NOT_OWNED_BY_PLAYER;
  this->_hashtab[Error::CAPACITY_IS_NOT_IN_LIST] = ::Error::CAPACITY_IS_NOT_IN_LIST;
  this->_hashtab[Error::CAPACITY_CANNOT_BE_USED] = ::Error::CAPACITY_CANNOT_BE_USED;
  this->_hashtab[Error::ITEM_IS_NOT_OWNED_BY_TEAM] = ::Error::ITEM_IS_NOT_OWNED_BY_TEAM;
  this->_hashtab[Error::UNKNOWN_PLAYER] = ::Error::UNKNOWN_PLAYER;
  this->_hashtab[Error::PLAYER_IS_NOT_IN_THE_SAME_TEAM] = ::Error::PLAYER_IS_NOT_IN_THE_SAME_TEAM;
  this->_hashtab[Error::ITEM_IS_NOT_CORRECT] = ::Error::ITEM_IS_NOT_CORRECT;
  this->_hashtab[Error::ITEM_CANNOT_BE_REMOVED_FROM_PRODUCTION_LIST] = ::Error::ITEM_CANNOT_BE_REMOVED_FROM_PRODUCTION_LIST;
  this->_hashtab[Error::HERO_CANNOT_CARRY_MORE_OBJECTS] = ::Error::HERO_CANNOT_CARRY_MORE_OBJECTS;
  this->_hashtab[Error::HERO_IS_NOT_CARRYING_THIS_ITEM] = ::Error::HERO_IS_NOT_CARRYING_THIS_ITEM;
  this->_hashtab[Error::OBJECT_IS_ALREADY_BEING_CARRIED] = ::Error::OBJECT_IS_ALREADY_BEING_CARRIED;
  this->_hashtab[Error::PLAYER_DOES_NOT_EXIST] = ::Error::PLAYER_DOES_NOT_EXIST;
  this->_hashtab[Error::PLAYER_IS_ALREADY_PRODUCING_AMELIORATION] = ::Error::PLAYER_IS_ALREADY_PRODUCING_AMELIORATION;
  this->_hashtab[Error::PLAYER_ALREADY_HAS_AMELIORATION] = ::Error::PLAYER_ALREADY_HAS_AMELIORATION;
  this->_hashtab[Error::ITEM_HASNT_GOT_CAPACITY] = ::Error::ITEM_HASNT_GOT_CAPACITY;
  this->_hashtab[Error::BUILDING_IS_ALREADY_BUILT] = ::Error::BUILDING_IS_ALREADY_BUILT;
  this->_hashtab[Error::ITEM_CANNOT_MOVE] = ::Error::ITEM_CANNOT_MOVE;
  this->_hashtab[Error::BUILDING_IS_NOT_BUILT] = ::Error::BUILDING_NOT_BUILT;
  this->_hashtab[Error::ITEM_CANNOT_ATTACK] = ::Error::ITEM_CANNOT_ATTACK;
  this->_hashtab[Error::CAPACITY_CANNOT_BE_AUTOMATIC] = ::Error::CAPACITY_CANNOT_BE_AUTOMATIC;

  this->_objectTypes.push_back(::Game::OBJECT);
  this->_objectTypes.push_back(::Game::PROJECTILE);
  this->_objectTypes.push_back(::Game::UNIT);
  this->_objectTypes.push_back(::Game::HERO);
  this->_objectTypes.push_back(::Game::BUILDING);
}

Game::Controller::~Controller(void) {
  delete this->_mutex;
  for (auto it : this->_races) {
    if (it.second) {
      Factory::Game::Race::remove(it.second);
    }
  }
}

::Error::Code	Game::Controller::translate(Game::Controller::Error::Type error) const {
  if (this->_hashtab.find(error) == this->_hashtab.end()) {
    return (::Error::UNDEF);
  }
  return (this->_hashtab.at(error));
}

Game::Controller::Error::Type Game::Controller::translate(::Error::Code error) const {
  for (auto it : this->_hashtab) {
    if (it.second == error) {
      return (it.first);
    }
  }
  return (Error::UNDEFINED);
}

const Game::Controller::Container	&Game::Controller::getRaces(void) const {
  return (this->_races);
}

const Game::Race	*Game::Controller::getRaceNamed(const std::string &filename,
							const std::string &name) const {
  ScopeLock s(this->_mutex);
  if (this->_fRaces.find(filename) == this->_fRaces.end() ||
      this->_fRaces.at(filename).empty() == true) {
    return (NULL);
  }
  for (auto it : this->_fRaces.at(filename)) {
    if (this->_races.find(it) != this->_races.end() && this->_races.at(it) && this->_races.at(it)->getName() == name) {
      return (this->_races.at(it));
    }
  }
  return (NULL);
}

const Game::Race	*Game::Controller::getRace(const Kernel::Serial &serial) const {
  return (get(serial, this->_races));
}

const Game::Controller::Container	Game::Controller::flushRaces(void) {
  Container c = this->_races;
  this->_races.clear();
  return (c);
}

void	Game::Controller::addRace(const std::string &filename, Game::Race *race) {
  ScopeLock s(this->_mutex);
  Logger::getInstance()->logf("Adding race [%s] to Controller", Logger::INFORMATION, &(race->serial()));
  this->_races[race->serial()] = race;
  this->_fRaces[filename].push_back(race->serial());
}

void	Game::Controller::removeRace(Game::Race *race) {
  this->removeRace(race->serial());
}

void	Game::Controller::removeRace(const Kernel::Serial &serial) {
  ScopeLock s(this->_mutex);
  for (auto &it : this->_fRaces) {
    it.second.remove(serial);
  }
  this->_races.erase(serial);
}

bool	Game::Controller::checkRessources(const Game::Player *player, const Kernel::Serial &serial, Game::Controller::Error::Type &error) const {
  const Kernel::Cost *cost = Kernel::Manager::getInstance()->getCost(serial);
  const Kernel::Data *data = Kernel::Manager::getInstance()->getData(serial);
  Game::Ressources rs = cost->ressources;
  if (data->type == ::Game::BUILDING) {
    rs.set(Game::Ressources::FOOD, 0);
  }
  if (player->hasEnoughRessources(rs)) {
    return (true);
  }
  error = Game::Controller::Error::NOT_ENOUGH_RESSOURCES;
  return (false);
}

bool	Game::Controller::checkRequirements(const Game::Player *player, const Game::Requirements *requirements, Game::Controller::Error::Type &error) const {
  if (requirements->fullfilledByPlayer(player) == false) {
    error = Game::Controller::Error::REQUIREMENTS_NOT_FULLFILLED;
    return (false);
  }
  return (true);
}

bool	Game::Controller::checkIfBuildingCanBuildUnit(const Game::AElement *building, const Kernel::Serial &serial, Game::Controller::Error::Type &error) const {
  if (building->isBuilt() == false) {
    error = Error::BUILDING_IS_NOT_BUILT;
    return (false);
  }
  if (std::find(building->getInfos().building->units.begin(), building->getInfos().building->units.end(), serial) == building->getInfos().building->units.end()) {
    error = Error::BUILDING_CANNOT_BUILD_THIS_UNIT;
    return (false);
  }
  return (true);
}

bool	Game::Controller::checkIfItemExists(const Kernel::Serial &item, Game::Controller::Error::Type &error) const {
  if (!Kernel::Manager::getInstance()->getData(item)) {
    error = Game::Controller::Error::UNKNOWN_ITEM;
    Logger::getInstance()->logf("Item unknown : %s", Logger::FATAL, &item);
    return (false);
  }
  return (true);
}

bool	Game::Controller::checkIfUnitIsInRace(const Game::Race *race, const Kernel::Serial &unit, Game::Controller::Error::Type &error) const {
  if (!race->getUnitRequirements(unit)) {
    error = Game::Controller::Error::ITEM_NOT_IN_RACE;
    return (false);
  }
  return (true);
}

bool	Game::Controller::checkIfItemIsInRace(const Game::Race *race, const Kernel::Serial &item, Game::Controller::Error::Type &error) const {
  if (!race->getUnitRequirements(item) && !race->getBuildingRequirements(item) && !race->getHeroRequirements(item)) {
    error = Game::Controller::Error::ITEM_NOT_IN_RACE;
    return (false);
  }
  return (true);
}

bool	Game::Controller::checkIfItemIsOwnedByPlayer(const Game::Player *player, const Game::AElement *item, Game::Controller::Error::Type &error) const {
  if (player != item->getPlayer()) {
    error = Game::Controller::Error::ITEM_IS_NOT_OWNED_BY_PLAYER;
    return (false);
  }
  return (true);
}

bool	Game::Controller::checkIfBuildingIsInRace(const Game::Race *race, const Kernel::Serial &serial, Game::Controller::Error::Type &error) const {
  if (!race->getBuildingRequirements(serial)) {
    error = Game::Controller::Error::ITEM_NOT_IN_RACE;
    return (false);
  }
  return (true);
}

bool	Game::Controller::checkIfCapacityIsInList(const Kernel::Serial &item, const Kernel::Serial &serial,
						  Game::Controller::Error::Type &error) const {
  const Kernel::CapacityList *list = Kernel::Manager::getInstance()->getCapacityList(item);
  if (std::find(list->list.begin(), list->list.end(), serial) == list->list.end()) {
    error = Error::CAPACITY_IS_NOT_IN_LIST;
    return (false);
  }
  return (true);
}

bool	Game::Controller::checkIfItemHasEnoughSelfRessources(const Game::AElement *element, const Kernel::Serial &serial, Game::Controller::Error::Type &error) const {
  const Kernel::ElementRessources &ressources = element->getRessources();
  const Kernel::Cost *cost = Kernel::Manager::getInstance()->getCost(serial);
  if (!ressources.hasEnough(cost->personnalRessource)) {
    error = Error::NOT_ENOUGH_SELF_RESSOURCES;
    return (false);
  }
  return (true);
}

bool	Game::Controller::checkIfCapacityIsNotPassive(const Kernel::Serial &serial, Game::Controller::Error::Type &error) const {
  if (Kernel::Manager::getInstance()->getCapacityData(serial)->passive) {
    error = Error::CAPACITY_CANNOT_BE_USED;
    return (false);
  }
  return (true);
}

bool	Game::Controller::checkIfItemIsOwnedByTeam(const Game::Player *player, const Game::AElement *element, Game::Controller::Error::Type &error) const {
  if (!this->checkIfPlayersAreAllied(player, element->getPlayer(), error)) {
    error = Error::ITEM_IS_NOT_OWNED_BY_TEAM;
    return (false);
  }
  return (true);
}

bool	Game::Controller::checkIfPlayersAreAllied(const Game::Player *lhs, const Game::Player *rhs, Game::Controller::Error::Type &error) const {
  if (lhs->isAlliedWith(rhs) == false) {
    error = Error::PLAYER_IS_NOT_IN_THE_SAME_TEAM;
    return (false);
  }
  return (true);
}

bool	Game::Controller::checkIfItemIs(const Game::AElement *item, ::Game::Type type, Game::Controller::Error::Type &error) const {
  if (type != item->getType()) {
    error = Error::ITEM_IS_NOT_CORRECT;
    return (false);
  }
  return (true);
}

bool	Game::Controller::checkIfItemIsLast(const Game::Building *item, const Kernel::Serial &serial, Game::Controller::Error::Type &error) const {
  if (item->backQueue() != serial) {
    error = Error::ITEM_CANNOT_BE_REMOVED_FROM_PRODUCTION_LIST;
    return (false);
  }
  return (true);
}

bool	Game::Controller::checkIfHeroCanCarryMoreObjects(const Game::Hero *hero, Game::Controller::Error::Type &error) const {
  if (hero->canPickUpObject() == false) {
    error = Error::HERO_CANNOT_CARRY_MORE_OBJECTS;
    return (false);
  }
  return (true);
}

bool	Game::Controller::checkHandRange(const Game::AElement *element, double x1, double y1, double z1,
					 double x2, double y2, double z2) const {
  double vx = x1 - x2;
  double vy = y1 - y2;
  double vz = z1 - z2;
  double hb = element->getInfos().data->hitbox;
  return (vx * vx + vy * vy + vz * vz <= hb * hb);
}

bool	Game::Controller::checkHandRange(const Game::AElement *element, double x1, double y1, double z1) const {
  return (this->checkHandRange(element, element->getX(), element->getY(), element->getZ(), x1, y1, z1));
}

bool	Game::Controller::checkIfHeroIsCarryingThisObject(const Game::Hero *hero, const Game::AElement *element,
							  Game::Controller::Error::Type &error) const {
  for (auto it : hero->getObjects()) {
    if (it->getID() == element->getID()) {
      return (true);
    }
  }
  error = Error::HERO_IS_NOT_CARRYING_THIS_ITEM;
  return (false);
}

bool	Game::Controller::checkHitboxesCollision(const Game::AElement *item1, const Game::AElement *item2) const {
  double vx = item1->getX() - item2->getX();
  double vy = item1->getY() - item2->getY();
  double vz = item1->getZ() - item2->getZ();
  //  double hb = item1->getInfos().data->hitbox + item2->getInfos().data->hitbox;
  return (vx * vx + vy * vy + vz * vz <= 1.0);
}

bool	Game::Controller::checkIfObjectCanBePickedUp(const Game::Object *object, Game::Controller::Error::Type &error) const {
  if (object->objectIsBeingCarried()) {
    error = Error::OBJECT_IS_ALREADY_BEING_CARRIED;
    return (false);
  }
  return (true);
}

bool	Game::Controller::checkIfAmeliorationIsLastInQueue(const Game::Player *player, const Kernel::Serial &type, const Kernel::Serial &amelioration, Game::Controller::Error::Type &error) const {
  if (player->backQueue(type) == amelioration) {
    return (true);
  }
  error = Error::ITEM_CANNOT_BE_REMOVED_FROM_PRODUCTION_LIST;
  return (false);
}

bool	Game::Controller::checkIfPlayerHasNotAmelioration(const Game::Player *player, const Kernel::Serial &type,
							  const Kernel::Serial &amelioration,
							  Game::Controller::Error::Type &error) const {
  if (player->hasAmelioration(type, amelioration) == true) {
    error = Error::PLAYER_ALREADY_HAS_AMELIORATION;
    return (false);
  }
  return (true);
}

bool	Game::Controller::checkIfPlayerIsNotProducingAmelioration(const Game::Player *player,
								  const Kernel::Serial &type,
								  const Kernel::Serial &amelioration,
								  Game::Controller::Error::Type &error) const {
  if (player->isInQueue(type, amelioration) == true) {
    error = Error::PLAYER_IS_ALREADY_PRODUCING_AMELIORATION;
    return (false);
  }
  return (true);
}

bool	Game::Controller::checkIfItemHasCapacity(const Game::AElement *item, const Kernel::Serial &capacity,
						 Game::Controller::Error::Type &error) const {
  if (item->hasCapacity(capacity) == false) {
    Logger::getInstance()->logf("No capacity : %s", Logger::FATAL, &capacity);
    error = Error::ITEM_HASNT_GOT_CAPACITY;
    return (false);
  }
  return (true);
}

bool	Game::Controller::checkIfBuildingIsNotBuilt(const Game::Building *building,
						    Game::Controller::Error::Type &error) const {
  if (building->isBuilt() == false) {
    return (true);
  }
  error = Error::BUILDING_IS_ALREADY_BUILT;
  return (false);
}

bool	Game::Controller::playerCanCreateUnit(const Game::Player *player, const Game::AElement *building,
					     const Kernel::Serial &unit, Game::Controller::Error::Type &error) const {
  const Game::Requirements *requirements = player->getRace()->getUnitRequirements(unit);
  return (this->checkIfItemExists(unit, error) &&
	  this->checkIfUnitIsInRace(player->getRace(), unit, error) &&
	  this->checkIfItemIsOwnedByPlayer(player, building, error) &&
	  this->checkIfItemIs(building, ::Game::BUILDING, error) &&
	  this->checkRessources(player, unit, error) &&
	  this->checkRequirements(player, requirements, error) &&
	  this->checkIfBuildingCanBuildUnit(building, unit, error));
}

bool	Game::Controller::playerCanBuildBuilding(const Game::Player *player, const Kernel::Serial &serial,
						 Game::Controller::Error::Type &error) const {
  const Game::Requirements *requirements = player->getRace()->getBuildingRequirements(serial);
  return (this->checkIfItemExists(serial, error) &&
	  this->checkIfBuildingIsInRace(player->getRace(), serial, error) &&
	  this->checkRessources(player, serial, error) &&
	  this->checkRequirements(player, requirements, error));
}

bool	Game::Controller::itemCanUseCapacity(const Game::AElement *element, const Kernel::Serial &serial,
					     Game::Controller::Error::Type &error) const {
  return (this->checkIfItemExists(serial, error) &&
	  this->checkIfCapacityIsInList(element->serial(), serial, error) &&
	  this->checkIfCapacityIsNotPassive(serial, error) &&
	  this->checkIfItemHasEnoughSelfRessources(element, serial, error));
}

bool	Game::Controller::playerCanChangeUnitStance(const Game::Player *player, const Game::AElement *unit, Game::Controller::Error::Type &error) const {
  return (this->checkIfItemIsOwnedByPlayer(player, unit, error));
}

bool	Game::Controller::playerCanAskUnitStance(const Game::Player *player, const Game::AElement *unit, Game::Controller::Error::Type &error) const {
  return (this->checkIfItemIsOwnedByTeam(player, unit, error));
}

bool	Game::Controller::playerCanAskItemInformations(const Game::Player *, const Game::AElement *,
						       Game::Controller::Error::Type &) const {
  return (true);
}

bool	Game::Controller::playerCanStopItemAction(const Game::Player *player, const Game::AElement *item,
						  Game::Controller::Error::Type &error) const {
  return (this->checkIfItemIsOwnedByPlayer(player, item, error));
}

bool	Game::Controller::playerCanAskItemAction(const Game::Player *, const Game::AElement *,
						 Game::Controller::Error::Type &) const {
  return (true);
}

bool	Game::Controller::playerCanAskPlayerRessources(const Game::Player *player, const Game::Player *oth,
						       Game::Controller::Error::Type &error) const {
  return (this->checkIfPlayersAreAllied(player, oth, error));
}

bool	Game::Controller::playerCanSetItemAction(const Game::Player *player, const Game::AElement *item,
						 Game::Controller::Error::Type &error) const {
  return (this->checkIfItemIsOwnedByPlayer(player, item, error));
}

bool	Game::Controller::playerCanRemoveUnitFromProductionList(const Game::Player *player,
								const Game::AElement *item,
								const Kernel::Serial &serial,
								Game::Controller::Error::Type &error) const {
  return (this->checkIfItemIs(item, ::Game::BUILDING, error) &&
	  this->checkIfItemIsOwnedByPlayer(player, item, error) &&
	  this->checkIfItemIsLast(reinterpret_cast<const Game::Building *>(item), serial, error));
}

bool	Game::Controller::playerCanAskHeroObjects(const Game::Player *, const Game::AElement *item,
						  Game::Controller::Error::Type &error) const {
  return (this->checkIfItemIs(item, ::Game::HERO, error));
}

bool	Game::Controller::playerCanAskHeroToPickUpObject(const Game::Player *player, const Game::Hero *hero,
							 const Game::Object *object,
							 Game::Controller::Error::Type &error) const {
  return (this->checkIfItemIs(hero, ::Game::HERO, error) &&
	  this->checkIfItemIs(object, ::Game::OBJECT, error) &&
	  this->checkIfItemIsOwnedByPlayer(player, hero, error) &&
	  this->checkIfHeroCanCarryMoreObjects(hero, error) &&
	  this->checkIfObjectCanBePickedUp(object, error));
}

bool	Game::Controller::playerCanAskHeroToReleaseObject(const Game::Player *player, const Game::Hero *hero,
							  const Game::Object *object,
							  Game::Controller::Error::Type &error) const {
  return (this->checkIfItemIs(hero, ::Game::HERO, error) &&
	  this->checkIfItemIs(object, ::Game::OBJECT, error) &&
	  this->checkIfItemIsOwnedByPlayer(player, hero, error) &&
	  this->checkIfHeroIsCarryingThisObject(hero, object, error) &&
	  this->checkIfObjectCanBePickedUp(object, error));
}

bool	Game::Controller::itemIsInRangeOfPoint(const Game::AElement *element, double x, double y, double z) const {
  return (this->checkHandRange(element, x, y, z));
}

bool	Game::Controller::itemIsInRangeOfItem(const Game::AElement *item1, const Game::AElement *item2) const {
  return (this->checkHitboxesCollision(item1, item2));
}

bool	Game::Controller::playerCanAskAmeliorations(const Game::Player *, const Game::Player *, Game::Controller::Error::Type &) const {
  return (true);
}

bool	Game::Controller::playerCanAskAmeliorations(const Game::Player *player, const Game::Player *otherPlayer, const Kernel::Serial &item, Game::Controller::Error::Type &error) const {
  return (this->playerCanAskAmeliorations(player, otherPlayer, error) &&
	  this->checkIfItemExists(item, error) &&
	  this->checkIfItemIsInRace(otherPlayer->getRace(), item, error));
}

bool	Game::Controller::playerCanRemoveAmeliorationFromProductionQueue(const Game::Player *player, const Kernel::Serial &type, const Kernel::Serial &amelioration, Game::Controller::Error::Type &error) const {
  return (this->checkIfItemExists(type, error) &&
	  this->checkIfItemIsInRace(player->getRace(), type, error) &&
	  this->checkIfItemExists(amelioration, error) &&
	  this->checkIfAmeliorationIsLastInQueue(player, type, amelioration, error));
}

bool	Game::Controller::playerCanProduceAmelioration(const Game::Player *player, const Kernel::Serial &type,
						       const Kernel::Serial &amelioration,
						       Game::Controller::Error::Type &error) const {
  return (this->checkIfItemExists(type, error) &&
	  this->checkIfItemIsInRace(player->getRace(), type, error) &&
	  this->checkIfItemExists(amelioration, error) &&
	  this->checkIfPlayerHasNotAmelioration(player, type, amelioration, error) &&
	  this->checkIfPlayerIsNotProducingAmelioration(player, type, amelioration, error) &&
	  this->checkRessources(player, amelioration, error));
}

bool	Game::Controller::checkIfBuildingCanBeBuilt(const Game::Building *building,
						    Game::Controller::Error::Type &error) const {
  if (building->getCurrentLife() < building->getMaxLife()) {
    return (true);
  }
  error = Error::BUILDING_IS_ALREADY_BUILT;
  return (false);
}

bool	Game::Controller::checkIfBuildingIsBuilt(const Game::Building *building,
						 Game::Controller::Error::Type &error) const {
  if (building->isBuilt() == false) {
    error = Error::BUILDING_IS_NOT_BUILT;
    return (false);
  }
  return (true);
}

bool	Game::Controller::playerCanAskUnitToBuild(const Game::Player *player, const Game::Unit *unit,
						  const Game::Building *building,
						  Game::Controller::Error::Type &error) const {
  return (this->checkIfItemIsOwnedByPlayer(player, unit, error) &&
	  this->checkIfItemIsOwnedByPlayer(player, building, error) &&
	  this->unitCanBuildBuilding(unit, building, error));
}

bool	Game::Controller::playerCanAskUnitToHarvestRessourcesSpot(const Game::Player *player,
								  const Game::AElement *unit,
								  const Game::AElement *spot,
								  Game::Controller::Error::Type &error) const {
  return (this->checkIfItemIs(unit, ::Game::UNIT, error) &&
	  this->checkIfItemIs(spot, ::Game::RESSSPOT, error) &&
	  this->checkIfItemIsOwnedByPlayer(player, unit, error) &&
	  this->checkIfItemHasCapacity(unit, Kernel::Config::getInstance()->getString(Kernel::Config::CARRY_RESSOURCES_CAPACITY), error) &&
	  this->checkIfItemHasCapacity(unit, Kernel::Config::getInstance()->getString(Kernel::Config::HARVEST_CAPACITY), error));
}

bool	Game::Controller::unitCanDepositInBuilding(const Game::AElement *unit, const Game::AElement *building,
						   ::Game::Ressources::Type type) const {
  Kernel::Serial capacity = "";
  switch (type) {
  case ::Game::Ressources::WOOD:
    capacity = Kernel::Config::getInstance()->getString(Kernel::Config::RECOVER_WOOD_CAPACITY);
    break;
  case ::Game::Ressources::GOLD:
    capacity = Kernel::Config::getInstance()->getString(Kernel::Config::RECOVER_GOLD_CAPACITY);
    break;
  default:
    return (false);
  }
  Error::Type error;
  return (this->checkIfItemIs(unit, ::Game::UNIT, error) &&
	  this->checkIfItemIs(building, ::Game::BUILDING, error) &&
	  this->checkIfItemIsOwnedByPlayer(unit->getPlayer(), building, error) &&
	  this->checkIfItemHasCapacity(building, capacity, error));
}

bool	Game::Controller::playerCanAskUnitPickedUpRessources(const Game::Player *, const Game::AElement *unit,
							     ::Game::Controller::Error::Type &error) const {
  return (this->checkIfItemIs(unit, ::Game::UNIT, error) &&
	  this->checkIfItemHasCapacity(unit, Kernel::Config::getInstance()->getString(Kernel::Config::CARRY_RESSOURCES_CAPACITY), error));
}

bool	Game::Controller::playerCanAskItemEffects(const Game::Player *, const Game::AElement *, Error::Type &) const {
  return (true);
}

bool	Game::Controller::itemIsInRangeOfPoint(const ::Game::AElement *element, double x1, double y1, double z1,
						double x2, double y2, double z2) const {
  return (this->checkHandRange(element, x1, y1, z1, x2, y2, z2));
}

bool	Game::Controller::checkAttackRange(const Game::AElement *element, double x, double y, double z) const {
  double vx, vy, vz, hb;
  vx = element->getX() - x;
  vy = element->getY() - y;
  vz = element->getZ() - z;
  hb = element->getAttackRange();
  return (vx * vx + vy * vy + vz * vz <= hb * hb);
}

bool	Game::Controller::itemHasAttackRangeOnItem(const Game::AElement *element, const Game::AElement *target) const {
  return (this->checkAttackRange(element, target->getX(), target->getY(), target->getZ()));
}

bool	Game::Controller::checkIfItemIsOneOfThese(const Game::AElement *item, int objType,
						  ::Game::Controller::Error::Type &error) const {
  for (auto it : this->_objectTypes) {
    if (it & objType) {
      if (item->getType() == it) {
	return (true);
      }
    }
  }
  error = Error::ITEM_CANNOT_MOVE;
  return (false);
}

bool	Game::Controller::playerCanMoveItem(const Game::Player *player, const Game::AElement *element,
					    ::Game::Controller::Error::Type &error) const {
  return (this->checkIfItemIsOwnedByPlayer(player, element, error) &&
	  this->itemCanMove(element, error));
}

bool	Game::Controller::checkIfItemCanAttack(const Game::AElement *item,
					      ::Game::Controller::Error::Type &error) const {
  if (dynamic_cast<const Game::CanUseCapacity *>(item) &&
      dynamic_cast<const Game::CanUseCapacity *>(item)->getAttackCapacity() != "") {
    if (this->itemCanUseCapacity(item, dynamic_cast<const Game::CanUseCapacity *>(item)->getAttackCapacity(), error)) {
      return (true);
    }
    return (false);
  }
  error = Error::ITEM_CANNOT_ATTACK;
  return (false);
}

bool	Game::Controller::checkIfItemCanBeAttacked(const Game::AElement *,
						   ::Game::Controller::Error::Type &) const {
  return (true);
}

bool	Game::Controller::playerCanAskItemToAttackItem(const Game::Player *player, const Game::AElement *item1,
						       const Game::AElement *item2,
						       ::Game::Controller::Error::Type &error) const {
  return (this->checkIfItemIsOwnedByPlayer(player, item1, error) &&
	  this->checkIfItemCanAttack(item1, error) &&
	  this->checkIfItemCanBeAttacked(item2, error));
}

bool	Game::Controller::itemHasVisionOnItem(const Game::Map *map, const Game::AElement *source,
					     const Game::AElement *target) const {
  return (map->hasVision(source->getPlayer()->getTeam(), target->getX(), target->getY(), target->getZ()));
}

bool	Game::Controller::playerCanAskUnitToPatrol(const Game::Player *player, const Game::AElement *item,
						   ::Game::Controller::Error::Type &error) const {
  return (this->checkIfItemIsOneOfThese(item, ::Game::HERO | ::Game::UNIT, error) &&
	  this->checkIfItemHasCapacity(item,
				       Kernel::Config::getInstance()->getString(Kernel::Config::PATROL_CAPACITY),
				       error) &&
	  this->checkIfItemIsOwnedByPlayer(player, item, error));
}

bool	Game::Controller::unitCanBuildBuilding(const Game::Unit *unit, const Game::Building *building,
					       Game::Controller::Error::Type &error) const {
  return (this->checkIfItemIs(unit, ::Game::UNIT, error) &&
	  this->checkIfItemIs(building, ::Game::BUILDING, error) &&
	  this->checkIfItemHasCapacity(unit,
				       Kernel::Config::getInstance()->getString(Kernel::Config::BUILD_CAPACITY),
				       error) &&
	  this->checkIfBuildingCanBeBuilt(building, error));

}

bool	Game::Controller::itemCanMove(const Game::AElement *element, Game::Controller::Error::Type &error) const {
  return (this->checkIfItemIsOneOfThese(element, MOVABLE_OBJECTS, error));
}

bool	Game::Controller::checkIfItemCanAttackZone(const Game::AElement *item, Error::Type &error) const {
  if (dynamic_cast<const Game::CanUseCapacity *>(item) &&
      dynamic_cast<const Game::CanUseCapacity *>(item)->getAttackZoneCapacity() != "") {
    if (this->itemCanUseCapacity(item, dynamic_cast<const Game::CanUseCapacity *>(item)->getAttackZoneCapacity(), error)) {
      return (true);
    }
    return (false);
  }
  error = Error::ITEM_CANNOT_ATTACK;
  return (true);
}

bool	Game::Controller::itemHasAttackRangeOnPoint(const Game::AElement *item, double x, double y, double z) const {
  return (this->checkAttackRange(item, x, y, z));
}

bool	Game::Controller::playerCanAskItemToAttackZone(const Game::Player *player, const Game::AElement *item,
						       Game::Controller::Error::Type &error) const {
  return (this->checkIfItemIsOwnedByPlayer(player, item, error) &&
	  this->checkIfItemCanAttackZone(item, error));
}

bool	Game::Controller::itemHasVisionOnPoint(const Game::Map *map, const Game::AElement *item,
					       double x, double y, double z) const {
  return (map->hasVision(item->getPlayer()->getTeam(), x, y, z));
}

bool	Game::Controller::playerCanAskItemToUseCapacity(const Game::Player *player, const Game::AElement *item,
							const Kernel::Serial &capacity, Error::Type &error) const {
  return (this->checkIfItemIsOwnedByPlayer(player, item, error) &&
	  this->itemCanUseCapacity(item, capacity, error));
}

bool	Game::Controller::checkIfCapacityCanBeAutomatic(const Kernel::Serial &capacity, Error::Type &error) const {
  const Kernel::CapacityData *data = Kernel::Manager::getInstance()->getCapacityData(capacity);
  if (data->canAuto == false) {
    error = Error::CAPACITY_CANNOT_BE_AUTOMATIC;
    return (false);
  }
  return (true);
}

bool	Game::Controller::playerCanAskItemToSetCapacityAutomatic(const Game::Player *player,
								 const Game::AElement *item,
								 const Kernel::Serial &capacity,
								 Error::Type &error) const {
  return (this->checkIfItemIsOwnedByPlayer(player, item, error) &&
	  this->checkIfItemHasCapacity(item, capacity, error) &&
	  this->checkIfCapacityCanBeAutomatic(capacity, error));
}

bool	Game::Controller::playerCanCreateBuilding(const Game::Player *player,
						  const Kernel::Serial &building,
						  Error::Type &error) const {
  return (this->checkIfItemIsInRace(player->getRace(), building, error) &&
	  this->checkRessources(player, building, error));
}
