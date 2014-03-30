//
// CanUseCapacity.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Fri Feb 21 10:59:30 2014 geoffrey bauduin
// Last update Thu Mar 13 16:59:22 2014 geoffrey bauduin
//

#ifndef GAME_CANUSECAPACITY_HPP_
# define GAME_CANUSECAPACITY_HPP_

#include	"IFromFactory.hpp"
#include	"Game/AElement.hpp"
#include	"Threading/ScopeLock.hpp"

namespace	Game {

  class	CanUseCapacity: virtual public Game::AElement, virtual public IFromFactory {

  private:
    mutable Mutex	*_mutex;

  protected:
    Kernel::ID::id_t	_target;
    ::Game::Type	_targetType;
    bool		_isAttacking;
    Vector3d		_targetZone;

  private:
    Kernel::Serial	_attackCapacity;
    Kernel::Serial	_attackZoneCapacity;

  public:
    CanUseCapacity(void);
    virtual ~CanUseCapacity(void);

    void	init(void);
    virtual void	destroy(void);

    bool	isAttacking(void) const;
    Kernel::ID::id_t	getTarget(void) const;
    ::Game::Type	getTargetType(void) const;

    virtual void	setTarget(double, double, double);
    virtual void	setTarget(Kernel::ID::id_t, ::Game::Type);
    virtual void	removeTarget(void);

    virtual void	attack(const Game::AElement *);

    const Kernel::Serial	&getAttackCapacity(void) const;
    const Kernel::Serial	&getAttackZoneCapacity(void) const;

  };

}

#endif
