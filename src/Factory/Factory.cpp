//
// Factory.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Jan 21 14:45:52 2014 geoffrey bauduin
// Last update Sun Mar 30 14:56:13 2014 geoffrey bauduin
//

#include	"Factory/Factory.hpp"
#include	"Factory/Kernel.hpp"
#include	"Factory/Protocol.hpp"
#ifdef __SERVER__
# include	"Factory/Network.hpp"
#endif
#include	"Factory/Game.hpp"
#include	"Logger.hpp"
#include	"Factory/Pool.hpp"

static Pool< ::Clock> *poolClock = NULL;

void	Factory::init(void) {
  Logger::getInstance()->log("Initializing pools ...", Logger::INFORMATION);
  Factory::Kernel::init();
  Factory::Game::init();
  Factory::Protocol::init();
#ifdef __SERVER__
  Factory::Network::init();
#endif
  poolClock = new Pool< ::Clock>(100, 50, "Clock");
  Logger::getInstance()->log("Pools have been initialized", Logger::INFORMATION);
}

void	Factory::end(void) {
  delete poolClock;
  Factory::Kernel::end();
  Factory::Game::end();
  Factory::Protocol::end();
#ifdef __SERVER__
  Factory::Network::end();
#endif 
}

::Clock	*Factory::Clock::create(void) {
  ::Clock *item = poolClock->get();
  return (item);
}

void	Factory::Clock::remove(::Clock *clock) {
  clock->destroy();
  poolClock->push(clock);
}
