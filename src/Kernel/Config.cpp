//
// Config.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Feb 25 21:45:09 2014 geoffrey bauduin
// Last update Tue Mar 25 10:03:51 2014 geoffrey bauduin
//

#include	"Kernel/Config.hpp"
#include	"Logger.hpp"
#include	"Parser/JSON.hpp"

Kernel::Config::Config(void):
  _pstrings(), _pdoubles(), _hashtab(), _pTypes(), _dflt("") {

  this->_hashtab["HP_REGEN_TIMER"] = HP_REGEN_TIMER;
  this->_pTypes[HP_REGEN_TIMER] = {DOUBLE, 5.0, ""};

  this->_hashtab["RESS_REGEN_TIMER"] = RESS_REGEN_TIMER;
  this->_pTypes[RESS_REGEN_TIMER] = {DOUBLE, 5.0, ""};

  this->_hashtab["DAY_NIGHT_SWITCH_TIMER"] = DAY_NIGHT_SWITCH_TIMER;
  this->_pTypes[DAY_NIGHT_SWITCH_TIMER] = {DOUBLE, 300.0, ""};

  this->_hashtab["BUILD_BUILDING_TIME_BETWEEN_TICKS"] = BUILD_BUILDING_TIME_BETWEEN_TICKS;
  this->_pTypes[BUILD_BUILDING_TIME_BETWEEN_TICKS] = {DOUBLE, 1.0, ""};

  this->_hashtab["BUILD_BUILDERS_AMOUNT_PER_TICK"] = BUILD_BUILDERS_AMOUNT_PER_TICK;
  this->_pTypes[BUILD_BUILDERS_AMOUNT_PER_TICK] = {DOUBLE, 1.0, ""};

  this->_hashtab["HARVEST_TIME_BETWEEN_TICKS"] = HARVEST_TIME_BETWEEN_TICKS;
  this->_pTypes[HARVEST_TIME_BETWEEN_TICKS] = {DOUBLE, 1.0, ""};

  this->_hashtab["HARVEST_AMOUNT_PER_TICK"] = HARVEST_AMOUNT_PER_TICK;
  this->_pTypes[HARVEST_AMOUNT_PER_TICK] = {DOUBLE, 1.0, ""};

  this->_hashtab["RESSOURCES_SPOT_DFLT_CAPACITY"] = RESSOURCES_SPOT_DEFAULT_CAPACITY;
  this->_pTypes[RESSOURCES_SPOT_DEFAULT_CAPACITY] = {DOUBLE, 1000.0, ""};

  this->_hashtab["MAX_HARVESTERS_ON_SPOT"] = MAX_HARVESTERS_ON_SPOT;
  this->_pTypes[MAX_HARVESTERS_ON_SPOT] = {DOUBLE, 6.0, ""};

  this->_hashtab["HARVESTER_CAPACITY"] = HARVESTER_CAPACITY;
  this->_pTypes[HARVESTER_CAPACITY] = {DOUBLE, 15.0, ""};

  this->_hashtab["UPDATES_PER_SECOND"] = UPDATES_PER_SECOND;
  this->_pTypes[UPDATES_PER_SECOND] = {DOUBLE, 60.0, ""};

  this->_hashtab["BASE_DELAY_BETWEEN_ATTACKS"] = BASE_DELAY_BETWEEN_ATTACKS;
  this->_pTypes[BASE_DELAY_BETWEEN_ATTACKS] = {DOUBLE, 1.0, ""};

  this->_hashtab["CRIT_CHANCE_MULTIPLIER"] = CRIT_CHANCE_MULTIPLIER;
  this->_pTypes[CRIT_CHANCE_MULTIPLIER] = {DOUBLE, 1.75, ""};

  this->_hashtab["MOVE_TEST_NUMBER"] = MOVE_TEST_NUMBER;
  this->_pTypes[MOVE_TEST_NUMBER] = {DOUBLE, 10.0, ""};

  this->_hashtab["BUILD_CAPACITY"] = BUILD_CAPACITY;
  this->_pTypes[BUILD_CAPACITY] = {STRING, 0.0, "BUILDBUILDINGCAPACITY"};

  this->_hashtab["CARRY_RESSOURCES_CAPACITY"] = CARRY_RESSOURCES_CAPACITY;
  this->_pTypes[CARRY_RESSOURCES_CAPACITY] = {STRING, 0.0, "CARRYRESSOURCESCAPACITY"};

  this->_hashtab["HARVEST_CAPACITY"] = HARVEST_CAPACITY;
  this->_pTypes[HARVEST_CAPACITY] = {STRING, 0.0, "HARVESTCAPACITY"};

  this->_hashtab["RECOVER_GOLD_CAPACITY"] = RECOVER_GOLD_CAPACITY;
  this->_pTypes[RECOVER_GOLD_CAPACITY] = {STRING, 0.0, "RECOVERGOLDCAPACITY"};

  this->_hashtab["RECOVER_WOOD_CAPACITY"] = RECOVER_WOOD_CAPACITY;
  this->_pTypes[RECOVER_WOOD_CAPACITY] = {STRING, 0.0, "RECOVERWOODCAPACITY"};

  this->_hashtab["HERO_OBJECTS_NUMBER"] = HERO_OBJECTS_NUMBER;
  this->_pTypes[HERO_OBJECTS_NUMBER] = {DOUBLE, 6.0, ""};

  this->_hashtab["PATROL_CAPACITY"] = PATROL_CAPACITY;
  this->_pTypes[PATROL_CAPACITY] = {STRING, 6.0, "PATROLCAPACITY"};

  this->_hashtab["UPDATE_ITEM_MAX_ELAPSED_TIME"] = UPDATE_ITEM_MAX_ELAPSED_TIME;
  this->_pTypes[UPDATE_ITEM_MAX_ELAPSED_TIME] = {DOUBLE, 3.0, ""};

  this->_hashtab["START_WOOD"] = START_WOOD;
  this->_pTypes[START_WOOD] = {DOUBLE, 500.0, ""};

  this->_hashtab["START_GOLD"] = START_GOLD;
  this->_pTypes[START_WOOD] = {DOUBLE, 200.0, ""};

  this->_hashtab["START_FOOD"] = START_FOOD;
  this->_pTypes[START_FOOD] = {DOUBLE, 10.0, ""};

  this->_hashtab["START_UNIT"] = START_UNIT;
  this->_pTypes[START_UNIT] = {DOUBLE, 3.0, ""};

  this->_hashtab["XP_UNIT"] = XP_UNIT;
  this->_pTypes[XP_UNIT] = {DOUBLE, 50.0, ""};

  this->_hashtab["XP_BUILDING"] = XP_BUILDING;
  this->_pTypes[XP_BUILDING] = {DOUBLE, 200.0, ""};

  this->_hashtab["TIMER_OUT_OF_COMBAT"] = TIMER_OUT_OF_COMBAT;
  this->_pTypes[TIMER_OUT_OF_COMBAT] = {DOUBLE, 10.0, ""};

  this->_hashtab["WOOD_SPOT_SERIAL"] = WOOD_SPOT_SERIAL;
  this->_pTypes[WOOD_SPOT_SERIAL] = {STRING, 0.0, "WOODSPOT"};

  this->_hashtab["GOLD_SPOT_SERIAL"] = GOLD_SPOT_SERIAL;
  this->_pTypes[GOLD_SPOT_SERIAL] = {STRING, 0.0, "GOLDSPOT"};

  this->_hashtab["SPEC_DELAY"] = SPEC_DELAY;
  this->_pTypes[SPEC_DELAY] = {DOUBLE, 180.0, ""};

  this->_hashtab["MAP_PRECISION"] = MAP_PRECISION;
  this->_pTypes[MAP_PRECISION] = {DOUBLE, 3.0, ""};

  this->_hashtab["MISS_CHANCE"] = MISS_CHANCE;
  this->_pTypes[MISS_CHANCE] = {DOUBLE, 5.0, ""};

  this->parseFile("./config/server.json");
}

Kernel::Config::~Config(void) {
}

void	Kernel::Config::parseFile(const std::string &filename) {
  Json::Value	root;
  Parser::JSON::getInstance()->parse(filename, root);
  Logger::getInstance()->addDecalage();
  for (auto it : this->_hashtab) {
    if (root.isMember(it.first)) {
      if (this->_pTypes[it.second].type == DOUBLE) {
	this->_pdoubles[it.second] = root[it.first].asDouble();
      }
      else {
	this->_pstrings[it.second] = root[it.first].asString();
      }
    }
    else {
      Logger::getInstance()->logf("Cannot find >%s< in >%s<", Logger::FATAL, &it.first, &filename);
      if (this->_pTypes[it.second].type == DOUBLE) {
	this->_pdoubles[it.second] = this->_pTypes[it.second].d;
      }
      else {
	this->_pstrings[it.second] = this->_pTypes[it.second].s;
      }
    }
  }
  Logger::getInstance()->removeDecalage();
}

double	Kernel::Config::getDouble(Kernel::Config::Parameter p) const {
  if (this->_pdoubles.find(p) != this->_pdoubles.end()) {
    return (this->_pdoubles.at(p));
  }
  Logger::getInstance()->logf("Bad Kernel::Config::get (double) parameter >%p<", Logger::FATAL, p);
  return (1.0);
}

const std::string	&Kernel::Config::getString(Kernel::Config::Parameter p) const {
  if (this->_pstrings.find(p) != this->_pstrings.end()) {
    return (this->_pstrings.at(p));
  }
  Logger::getInstance()->logf("Bad Kernel::Config::get (string) parameter >%p<", Logger::FATAL, p);
  return (this->_dflt);
}

unsigned int	Kernel::Config::getUInt(Kernel::Config::Parameter p) const {
  return (static_cast<unsigned int>(this->getDouble(p)));
}
