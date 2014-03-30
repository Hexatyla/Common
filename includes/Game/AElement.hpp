//
// AElement.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 17:08:18 2014 geoffrey bauduin
// Last update Tue Mar 25 10:13:17 2014 geoffrey bauduin
//

#ifndef GAME_AELEMENT_HPP_
# define GAME_AELEMENT_HPP_

#include	<list>
#include	<vector>
#include	<string>
#include	<map>
#include	<deque>
#include	"Game/Type.hpp"
#include	"Game/Capacity.hpp"
#include	"Game/Position.hpp"
#include	"Game/ABase.hpp"
#include	"HasID.hpp"
#include	"Kernel/ElementRessources.hpp"
#include	"Game/Effect.hpp"
#include	"Threading/Mutex.hpp"
#include	"IFromFactory.hpp"

namespace Game { class Player; class Race; class Action; }

namespace	Game {

  class AElement: virtual public Game::ABase, virtual public HasID, virtual public Game::Position, virtual public IFromFactory {

  public:
    typedef std::map<Kernel::Serial, std::deque<Game::Effect *> > EffectContainer;

  protected:
    mutable Mutex			*_actionMutex;
  private:
    mutable Mutex			*_ressourcesMutex;

  protected:
    mutable Mutex			*_effectsMutex;
    Kernel::ElementRessources		_ressources;
    std::map<Kernel::Serial, Game::Capacity *>	_capacities;
    unsigned int			_speed;
    Game::Action			*_action;
    EffectContainer			_effects;
    std::list<const Game::Effect *>	_temporaryEffects;
    mutable Mutex			*_elementMutex;
    bool				_built;

    virtual unsigned int	getUIntFromData(void *) const;
    virtual double		getDoubleFromData(void *) const;

    virtual void	_endAction(void);

    virtual void	_setAction(Game::Action *);
    virtual void	_stopAction(void);

  public:
    AElement(void);
    virtual ~AElement(void);

    void	init(unsigned int, const std::string &, const Game::Player *, Game::Type, int, double, double, double);
    virtual void	destroy(void);

    bool	canPassThrough(const ::Game::AElement *) const;
    void	setSpeed(unsigned int);

    unsigned int getCurrentLife(void) const;
    unsigned int getCurrentRessources(void) const;
    const Kernel::ElementRessources &getRessources(void) const;

    const Game::Action	*getAction(void) const;
    virtual void	setAction(Game::Action *);
    virtual void	stopAction(void);
    virtual void	endAction(void);

    virtual void	addLife(unsigned int);
    virtual void	removeLife(unsigned int);

    void		setLife(unsigned int);
    void		setRessources(unsigned int);

    virtual bool	removeRessources(unsigned int, Kernel::ElementRessources::Type);

    virtual unsigned int	getSpeed(void) const;

    const std::map<Kernel::Serial, Game::Capacity *>	getCapacities(void) const;

    bool	hasCapacity(const Kernel::Serial &) const;
    bool	isBuilt(void) const;

    const EffectContainer	&getEffects(void) const;
    const std::list<const Game::Effect *> &getTemporaryEffects(void) const;

    virtual void	addEffect(const Kernel::Serial &);
    virtual void	addEffect(const Game::Effect *);
    virtual void	removeEffect(const Game::Effect *);
    virtual void	removeEffect(const Kernel::Serial &);

    virtual void	setCapacityAutomatic(const Kernel::Serial &, bool);

  };

}

#endif
