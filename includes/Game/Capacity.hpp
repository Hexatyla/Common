//
// Capacity.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Wed Jan 15 14:44:25 2014 geoffrey bauduin
// Last update Thu Mar 13 17:07:54 2014 geoffrey bauduin
//

#ifndef GAME_CAPACITY_HPP_
# define GAME_CAPACITY_HPP_

#include	"Game/ABase.hpp"
#include	"Kernel/ID.hpp"
#include	"Threading/Mutex.hpp"
#include	"IFromFactory.hpp"

namespace	Game {

  class	Capacity: virtual public Game::ABase, virtual public IFromFactory {

  public:
    enum	Target {
      ZONE,
      ITEM,
      NONE
    };

  protected:
    bool		_automatic;
    Kernel::ID::id_t	_owner;
    mutable Mutex	*_mutex;

  public:
    Capacity(void);
    virtual ~Capacity(void);

    void		init(const std::string &, bool, const Game::Player *, Kernel::ID::id_t);
    virtual void	destroy(void);

    virtual void	setAutomatic(bool);
    bool		isAutomatic(void) const;
    bool		canBeAutomatic(void) const;
    Kernel::ID::id_t	getOwner(void) const;

  };

}

#endif
