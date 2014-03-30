//
// data_struct.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sun Feb 16 15:05:59 2014 geoffrey bauduin
// Last update Tue Mar 25 17:20:59 2014 geoffrey bauduin
//

#ifndef STRUCT_DATA_HPP_
# define STRUCT_DATA_HPP_

#include	"Game/Type.hpp"
#include	"Kernel/ID.hpp"
#include	"Game/Stance.hpp"
#include	"Kernel/Serial.hpp"
#include	"Game/Player.hpp"
#include	"Game/eAction.hpp"

struct item_ {
  Kernel::ID::id_t id;
  Game::Type type;
};

struct updateItem: item_ {
  double		factor;
};

struct userPing {
  Kernel::ID::id_t playerID;
  double x;
  double y;
};

struct unitStance: item_ {
  Game::Stance::Type stance;
};

struct action: item_ {
  Game::eAction	action;
};

struct createItem {
  char serial[33];
  double x;
  double y;
  double z;
  int o;
  const Game::Player *player;
};

struct ameliorationfinished {
  Kernel::ID::id_t playerID;
  char type[33];
  char serial[33];
};

struct pickupobject {
  Kernel::ID::id_t hero;
  Kernel::ID::id_t object;
};

struct releaseobject {
  Kernel::ID::id_t hero;
  Kernel::ID::id_t object;
  double x;
  double y;
  double z;
};

struct build_ {
  Kernel::ID::id_t unit;
  Kernel::ID::id_t building;
};

struct harvest_ {
  Kernel::ID::id_t unit;
  Kernel::ID::id_t spot;
};

struct harvestAmount_: harvest_ {
  unsigned int amount;
  Game::Ressources::Type type;
};

struct deposit_ {
  Kernel::ID::id_t unit;
  Kernel::ID::id_t building;
  Game::Ressources::Type type;
};

struct effecttimeout {
  item_ item;
  Kernel::Serial effect;
};

struct onrange {
  item_	source;
  item_	target;
};

struct position {
  double x;
  double y;
  double z;
};

struct move_: position {
  Kernel::ID::id_t id;
  ::Game::Type	type;
};

struct release_ {
  Kernel::ID::id_t object;
  double x;
  double y;
  double z;
};

struct attack_ {
  item_	item1;
  item_	item2;
};

struct projectile_: createItem {
  item_	source;
  bool	targetItem;
  union {
    item_	target;
    position	destination;
  };
};

struct follow_ {
  item_	source;
  item_	target;
  double factor;
};

struct patrol_ {
  item_	item;
  double x;
  double y;
};

struct moveBetweenPoints {
  position	from;
  position	to;
  bool		way;
};

struct moveToPoint_ {
  item_	item;
  position	point;
  double factor;
};

struct attackPoint_ {
  item_	item;
  position	point;
};
struct useCapacity_ {
  item_	item;
  char	capacity[33];
  Game::Capacity::Target	type;
  union {
    item_	target;
    position	point;
  };
};

struct setAutomatic_ {
  item_		item;
  char		capacity[33];
  bool		automatic;
};

struct xp_ {
  Kernel::ID::id_t id;
  unsigned int amount;
};

#endif
