//
// Projectile.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 18:33:04 2014 geoffrey bauduin
// Last update Thu Mar 13 17:50:44 2014 geoffrey bauduin
//

#ifndef	GAME_PROJECTILE_HPP_
# define GAME_PROJECTILE_HPP_

#include	"Game/AElement.hpp"
#include	"Game/Movable.hpp"

namespace	Game {

  class	Projectile: virtual public Game::AElement, virtual public Game::Movable, virtual public IFromFactory {

  protected:
    mutable Mutex	*_mutex;
    unsigned int	_damageAmount;
    Kernel::ID::id_t	_sourceID;
    ::Game::Type	_sourceType;
    Kernel::ID::id_t	_targetID;
    ::Game::Type	_targetType;
    double		_critChance;
    Vector3d		_target;
    bool		_targetingItem;

  public:
    Projectile(void);
    virtual ~Projectile(void);

    void	init(unsigned int, const std::string &, const Game::Player *, int, double, double, double);
    virtual void	destroy(void);

    virtual void	setSource(const ::Game::AElement *);
    virtual void	setTarget(const ::Game::AElement *);
    virtual void	setTarget(double, double, double);

    Kernel::ID::id_t	getSourceID(void) const;
    ::Game::Type	getSourceType(void) const;

    Kernel::ID::id_t	getTargetID(void) const;
    ::Game::Type	getTargetType(void) const;

    virtual double	getCritChance(void) const;
    virtual unsigned int getAttack(void) const;
    const Vector3d	&getTarget(void) const;

  };

}

#endif
