//
// Hero.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 18:30:22 2014 geoffrey bauduin
// Last update Thu Mar 13 17:15:42 2014 geoffrey bauduin
//

#ifndef GAME_HERO_HPP_
# define GAME_HERO_HPP_

#include	"Game/Unit.hpp"
#include	"Game/Object.hpp"
#include	"Threading/Mutex.hpp"
#include	"IFromFactory.hpp"

namespace	Game {

  class	Hero: virtual public Game::Unit, virtual public IFromFactory {

  private:
    mutable Mutex		*_mutex;

  protected:
    std::list<Game::Object *>	_objects;

    virtual unsigned int	getUIntFromData(void *addr) const;
    virtual double		getDoubleFromData(void *addr) const;

  public:
    Hero(void);
    virtual ~Hero(void);

    void		init(unsigned int, const std::string &, const Game::Player *, int, double, double, double);
    virtual void	destroy(void);

    virtual void	addObject(Game::Object *);
    virtual void	removeObject(Game::Object *);
    bool		canPickUpObject(void) const;
    const std::list<Game::Object *> &getObjects(void) const;

  };

}

#endif
