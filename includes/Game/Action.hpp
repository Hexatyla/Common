//
// Action.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Wed Jan 29 17:01:49 2014 geoffrey bauduin
// Last update Mon Mar  3 00:06:08 2014 geoffrey bauduin
//

#ifndef GAME_ACTION_HPP_
# define GAME_ACTION_HPP_

#include	"Game/eAction.hpp"
#include	"data_struct.hpp"
#include	"IFromFactory.hpp"

namespace	Game {

  class	Action: virtual public IFromFactory {

  protected:
    Game::eAction	_type;

  public:
    union {
      position		move;
      Kernel::ID::id_t	building;
      release_		release;
      Kernel::ID::id_t	object;
      deposit_		deposit;
      Kernel::ID::id_t	spot;
      item_		target;
      moveBetweenPoints	patrol;
      position		zone;
      useCapacity_	useCapacity;
    };

  public:
    Action(void);
    virtual ~Action(void);

    void	init(Game::eAction);
    virtual void destroy(void);

    Game::eAction	getType(void) const;

  };

}

#endif
