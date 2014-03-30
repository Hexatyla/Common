//
// Game.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Wed Jan 22 13:40:20 2014 geoffrey bauduin
// Last update Wed Mar 19 17:14:19 2014 geoffrey bauduin
//

#include	"Factory/Game.hpp"
#include	"Factory/Pool.hpp"

static Pool< ::Game::Race>	*poolRace = NULL;
static Pool< ::Game::Map>	*poolMap = NULL;
static Pool< ::Game::Map::QuadTree> *poolQuadTree = NULL;
static Pool< ::Game::Map::Node> *poolNode = NULL;
static Pool< ::Game::Effect> *poolEffect = NULL;
static Pool< ::Game::ProductionQueue> *poolQueue = NULL;
static Pool< ::Game::Amelioration> *poolAmelioration = NULL;
static Pool< ::Game::Capacity> *poolCapacity = NULL;
static Pool< ::Game::Action> *poolAction = NULL;
static Pool< ::Game::Team>	*poolTeam = NULL;
static Pool< ::Game::Requirements> *poolReq = NULL;
#ifndef __SERVER__
static Pool< ::Game::Building> *poolBuilding = NULL;
static Pool< ::Game::Unit> *poolUnit = NULL;
static Pool< ::Game::Projectile> *poolProjectile = NULL;
static Pool< ::Game::Hero> *poolHero = NULL;
static Pool< ::Game::Object> *poolObject = NULL;
static Pool< ::Game::RessourcesSpot> *poolRessourcesSpot = NULL;
#endif

void	Factory::Game::init(void) {
  poolRace = new Pool< ::Game::Race>(100, 20, "Game::Race");
  poolMap = new Pool< ::Game::Map>(100, 20, "Game::Map");
  poolQuadTree = new Pool< ::Game::Map::QuadTree>(5000, 1000, "Game::Map::QuadTree");
  poolNode = new Pool< ::Game::Map::Node>(150000, 15000, "Game::Map::Node");
  poolEffect = new Pool< ::Game::Effect>(500, 100, "Game::Effect");
  poolQueue = new Pool< ::Game::ProductionQueue>(500, 100, "Game::ProductionQueue");
  poolAmelioration = new Pool< ::Game::Amelioration>(500, 100, "Game::Amelioration");
  poolCapacity = new Pool< ::Game::Capacity>(500, 175, "Game::Capacity");
  poolAction = new Pool< ::Game::Action>(500, 350, "Game::Action");
  poolTeam = new Pool< ::Game::Team>(100, 20, "Game::Team");
  poolReq = new Pool< ::Game::Requirements>(500, 200, "Game::Requirements");
#ifndef __SERVER__
  poolBuilding = new Pool< ::Game::Building>(50, 20, "Game::Building");
  poolUnit = new Pool< ::Game::Unit>(200, 50, "Game::Unit");
  poolProjectile = new Pool< ::Game::Projectile>(200, 50, "Game::Projectile");
  poolHero = new Pool< ::Game::Hero>(50, 20, "Game::Hero");
  poolObject = new Pool< ::Game::Object>(50, 20, "Game::Object");
  poolRessourcesSpot = new Pool< ::Game::RessourcesSpot>(50, 20, "Game::RessourcesSpot");
#endif
}

void	Factory::Game::end(void) {
  delete poolRace;
  delete poolMap;
  delete poolQuadTree;
  delete poolNode;
  delete poolEffect;
  delete poolQueue;
  delete poolAmelioration;
  delete poolCapacity;
  delete poolAction;
  delete poolTeam;
  delete poolReq;
#ifndef __SERVER__
  delete poolBuilding;
  delete poolUnit;
  delete poolProjectile;
  delete poolHero;
  delete poolObject;
  delete poolRessourcesSpot;
#endif
}

::Game::Race	*Factory::Game::Race::create(const std::string &name, const Kernel::Serial &serial) {
  ::Game::Race *item = poolRace->get();
  item->init(name, serial);
  return (item);
}

void	Factory::Game::Race::remove(::Game::Race *item) {
  item->destroy();
  poolRace->push(item);
}

::Game::Map	*Factory::Game::Map::create(unsigned int x, unsigned int y, const std::vector<unsigned int> &z) {
  ::Game::Map *item = poolMap->get();
  item->init(x, y, z);
  return (item);
}

void	Factory::Game::Map::remove(::Game::Map *item) {
  item->destroy();
  poolMap->push(item);
}

::Game::Map::QuadTree *Factory::Game::Map::QuadTree::create(double x, double y, double width, double height) {
  ::Game::Map::QuadTree *item = poolQuadTree->get();
  item->init(x, y, width, height);
  return (item);
}

void	Factory::Game::Map::QuadTree::remove(::Game::Map::QuadTree *item) {
  item->destroy();
  poolQuadTree->push(item);
}

::Game::Map::Node *Factory::Game::Map::Node::create(void) {
  ::Game::Map::Node *item = poolNode->get();
  item->init();
  return (item);
}

void	Factory::Game::Map::Node::remove(::Game::Map::Node *item) {
  item->destroy();
  poolNode->push(item);
}

::Game::Effect	*Factory::Game::Effect::create(const Kernel::Serial &serial, const ::Game::Player *player, Kernel::ID::id_t itemID) {
  ::Game::Effect *item = poolEffect->get();
  item->init(serial, player, itemID);
  return (item);
}

void	Factory::Game::Effect::remove(::Game::Effect *item) {
  item->destroy();
  poolEffect->push(item);
}

::Game::ProductionQueue	*Factory::Game::ProductionQueue::create(void) {
  ::Game::ProductionQueue *item = poolQueue->get();
  item->init();
  return (item);
}

void	Factory::Game::ProductionQueue::remove(::Game::ProductionQueue *item) {
  item->destroy();
  poolQueue->push(item);
}

::Game::Amelioration	*Factory::Game::Amelioration::create(const Kernel::Serial &serial, const Kernel::Serial &owner) {
  ::Game::Amelioration *item = poolAmelioration->get();
  item->init(serial, owner);
  return (item);
}

void	Factory::Game::Amelioration::remove(::Game::Amelioration *item) {
  item->destroy();
  poolAmelioration->push(item);
}

::Game::Capacity	*Factory::Game::Capacity::create(const Kernel::Serial &serial, bool isAuto, const ::Game::Player *player, ::Kernel::ID::id_t owner) {
  ::Game::Capacity *item = poolCapacity->get();
  item->init(serial, isAuto, player, owner);
  return (item);
}

void	Factory::Game::Capacity::remove(::Game::Capacity *item) {
  item->destroy();
  poolCapacity->push(item);
}


::Game::Action	*Factory::Game::Action::create(::Game::eAction action) {
  ::Game::Action *item = poolAction->get();
  item->init(action);
  return (item);
}

void	Factory::Game::Action::remove(::Game::Action *item) {
  item->destroy();
  poolAction->push(item);
}

::Game::Team*	Factory::Game::Team::create() {
  ::Game::Team *team = poolTeam->get();
  team->init();
  return (team);
}

void	Factory::Game::Team::remove(::Game::Team *team) {
  team->destroy();
  poolTeam->push(team);
}

::Game::Requirements	*Factory::Game::Requirements::create(void) {
  ::Game::Requirements *item = poolReq->get();
  item->init();
  return (item);
}

void	Factory::Game::Requirements::remove(::Game::Requirements *item) {
  item->destroy();
  poolReq->push(item);
}
#ifndef __SERVER__
::Game::Building	*Factory::Game::Building::create(unsigned int id, const Kernel::Serial &serial, const ::Game::Player *player, int orientation, double x, double y, double z) {
  ::Game::Building *item = poolBuilding->get();
  item->init(id, serial, player, orientation, x, y, z);
  return (item);
}

void	Factory::Game::Building::remove(::Game::Building *item) {
  item->destroy();
  poolBuilding->push(item);
}

::Game::Unit	*Factory::Game::Unit::create(unsigned int id, const Kernel::Serial &serial, const ::Game::Player *player, int orientation, double x, double y, double z) {
  ::Game::Unit *item = poolUnit->get();
  item->init(id, serial, player, orientation, x, y, z);
  return (item);
}

void	Factory::Game::Unit::remove(::Game::Unit *item) {
  item->destroy();
  poolUnit->push(item);
}

::Game::Hero	*Factory::Game::Hero::create(unsigned int id, const Kernel::Serial &serial, const ::Game::Player *player, int orientation, double x, double y, double z) {
  ::Game::Hero *item = poolHero->get();
  item->init(id, serial, player, orientation, x, y, z);
  return (item);
}

void	Factory::Game::Hero::remove(::Game::Hero *item) {
  item->destroy();
  poolHero->push(item);
}

::Game::Projectile	*Factory::Game::Projectile::create(unsigned int id, const Kernel::Serial &serial, const ::Game::Player *player, int orientation, double x, double y, double z) {
  ::Game::Projectile *item = poolProjectile->get();
  item->init(id, serial, player, orientation, x, y, z);
  return (item);
}

void	Factory::Game::Projectile::remove(::Game::Projectile *item) {
  item->destroy();
  poolProjectile->push(item);
}

::Game::Object	*Factory::Game::Object::create(unsigned int id, const Kernel::Serial &serial, int orientation, double x, double y, double z) {
  ::Game::Object *item = poolObject->get();
  item->init(id, serial, orientation, x, y, z);
  return (item);
}

void	Factory::Game::Object::remove(::Game::Object *item) {
  item->destroy();
  poolObject->push(item);
}

::Game::RessourcesSpot	*Factory::Game::RessourcesSpot::create(unsigned int id, double x, double y, double z, ::Game::Ressources::Type type, unsigned int amount) {
  ::Game::RessourcesSpot *item = poolRessourcesSpot->get();
  item->init(id, x, y, z, type, amount);
  return (item);
}

void	Factory::Game::RessourcesSpot::remove(::Game::RessourcesSpot *item) {
  item->destroy();
  poolRessourcesSpot->push(item);
}
#endif
