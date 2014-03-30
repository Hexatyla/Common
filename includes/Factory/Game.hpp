//
// Game.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Wed Jan 22 13:39:24 2014 geoffrey bauduin
// Last update Wed Mar 19 17:14:05 2014 geoffrey bauduin
//

#ifndef FACTORY_GAME_HPP_
# define FACTORY_GAME_HPP_

#include	"Game/Race.hpp"
#include	"Game/Map.hpp"
#include	"Game/Effect.hpp"
#include	"Game/ProductionQueue.hpp"
#include	"Game/Capacity.hpp"
#include	"Game/Action.hpp"
#include	"Game/Team.hpp"
#include	"Game/Requirements.hpp"
#ifndef __SERVER__
# include	"Game/Building.hpp"
# include	"Game/Projectile.hpp"
# include	"Game/Object.hpp"
# include	"Game/Hero.hpp"
# include	"Game/Unit.hpp"
# include	"Game/RessourcesSpot.hpp"
#endif

namespace	Factory {

  namespace	Game {

    void	init(void);
    void	end(void);

    class	Race {

    public:
      static ::Game::Race	*create(const std::string &, const ::Kernel::Serial &);
      static void		remove(::Game::Race *);

    };

    class	Map {

    public:
      static ::Game::Map *create(unsigned int, unsigned int, const std::vector<unsigned int> &);
      static void remove(::Game::Map *);

      class	QuadTree {

      public:
	static ::Game::Map::QuadTree *create(double, double, double, double);
	static void	remove(::Game::Map::QuadTree *);

      };

      class	Node {

      public:
	static ::Game::Map::Node *create(void);
	static void	remove(::Game::Map::Node *);

      };

    };

    class	Effect {

    public:
      static ::Game::Effect *create(const ::Kernel::Serial &, const ::Game::Player *, ::Kernel::ID::id_t);
      static void remove(::Game::Effect *);

    };

    class	ProductionQueue {

    public:
      static ::Game::ProductionQueue *create(void);
      static void	remove(::Game::ProductionQueue *);

    };

    class	Amelioration {

    public:
      static ::Game::Amelioration *create(const ::Kernel::Serial &, const ::Kernel::Serial &);
      static void remove(::Game::Amelioration *);

    };

    class	Capacity {

    public:
      static ::Game::Capacity *create(const ::Kernel::Serial &, bool, const ::Game::Player *, ::Kernel::ID::id_t);
      static void remove(::Game::Capacity *);

    };

    class	Action {

    public:
      static ::Game::Action *create(::Game::eAction);
      static void remove(::Game::Action *);

    };

    class	Team {
    public:
      static ::Game::Team	*create();
      static void		remove(::Game::Team* t);
    };

    class	Requirements {

    public:
      static ::Game::Requirements	*create(void);
      static void			remove(::Game::Requirements *);

    };

#ifndef __SERVER__
    class	Building {

    public:
      static ::Game::Building	*create(unsigned int id, const ::Kernel::Serial &serial,
                                      const ::Game::Player *player, int orientation,
                                      double x, double y, double z);
      static void		remove(::Game::Building *);

    };

    class	Unit {

    public:
      static ::Game::Unit	*create(unsigned int id, const ::Kernel::Serial &serial,
                                  const ::Game::Player *player, int orientation,
                                  double x, double y, double z);
      static void		remove(::Game::Unit *);

    };

    class	Hero {

    public:
      static ::Game::Hero	*create(unsigned int id, const ::Kernel::Serial &serial,
                                  const ::Game::Player *player, int orientation,
                                  double x, double y, double z);
      static void		remove(::Game::Hero *);

    };

    class	Projectile {

    public:
      static ::Game::Projectile	*create(unsigned int id, const ::Kernel::Serial &serial,
                                        const ::Game::Player *player, int orientation,
                                        double x, double y, double z);
      static void		remove(::Game::Projectile *);

    };

    class	Object {

    public:
      static ::Game::Object	*create(unsigned int id, const ::Kernel::Serial &serial, int orientation, double x, double y, double z);
      static void		remove(::Game::Object *);

    };

    class	RessourcesSpot {

    public:
      static ::Game::RessourcesSpot	*create(unsigned int id, double x, double y, double z, ::Game::Ressources::Type type, unsigned int amount);
      static void		remove(::Game::RessourcesSpot *);

    };

#endif
  }

}

#endif
