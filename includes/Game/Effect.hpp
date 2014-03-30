//
// Effect.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Jan 14 14:54:10 2014 geoffrey bauduin
// Last update Thu Mar 13 17:10:12 2014 geoffrey bauduin
//

#ifndef GAME_EFFECT_HPP_
# define GAME_EFFECT_HPP_

#include	"Game/ABase.hpp"
#include	"Kernel/ID.hpp"
#include	"IFromFactory.hpp"
#include	"Threading/Mutex.hpp"

namespace	Game {

  class	Effect: virtual public Game::ABase, virtual public IFromFactory {

  private:
    mutable Mutex	*_mutex;

  public:
    enum	Type {
      AURA,
      DOT,
      BUFF
    };

  protected:
    double	_percentage;
    Kernel::ID::id_t _owner;

  public:
    Effect(void);
    virtual ~Effect(void);

    void			init(const Kernel::Serial &, const Game::Player *, Kernel::ID::id_t);
    virtual void		destroy(void);

    double			getPercentage(void) const;
    void			setPercentage(double);
    Kernel::ID::id_t		getOwner(void) const;

  };

}

#endif
