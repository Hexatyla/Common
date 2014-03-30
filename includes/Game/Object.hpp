//
// Object.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Wed Feb  5 13:24:52 2014 geoffrey bauduin
// Last update Thu Mar 13 17:35:48 2014 geoffrey bauduin
//

#ifndef GAME_OBJECT_HPP_
# define GAME_OBJECT_HPP_

#include	"Game/AElement.hpp"
#include	"Threading/Mutex.hpp"
#include	"IFromFactory.hpp"

namespace	Game {

  class	Object: virtual public Game::AElement, virtual public IFromFactory {

  private:
    mutable Mutex		*_mutex;

  protected:
    Kernel::ID::id_t	_ownerID;

  public:
    Object(void);
    virtual ~Object(void);

    void	init(Kernel::ID::id_t, const Kernel::Serial &, int, double, double, double);
    virtual void	destroy(void);

    virtual void	setPosition(double, double, double);

    bool	objectIsBeingCarried(void) const;
    bool	pickUp(Kernel::ID::id_t);
    void	release(void);

  };

}

#endif
