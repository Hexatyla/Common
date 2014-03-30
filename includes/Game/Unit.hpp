//
// Unit.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 18:24:31 2014 geoffrey bauduin
// Last update Wed Mar 19 16:14:08 2014 geoffrey bauduin
//

#ifndef GAME_UNIT_HPP_
# define GAME_UNIT_HPP_

namespace Game { class Player; }

#include	"Game/AElement.hpp"
#include	"Game/Movable.hpp"
#include	"Game/Stance.hpp"
#include	"Game/Ressources.hpp"
#include	"Game/CanUseCapacity.hpp"
#include	"Threading/Mutex.hpp"
#include	"Game/Level.hpp"

#define	LEVEL_MAX	10

namespace	Game {

  class	Unit: virtual public Game::AElement, virtual public Game::Movable,
	      virtual public IFromFactory, virtual public Game::CanUseCapacity {

  private:
    mutable Mutex	*_stanceMutex;
    mutable Mutex	*_levelMutex;

    typedef std::map<unsigned int, Level::Data> levelTable;

    static const levelTable  createXPTable(void);

    static const levelTable	_xpTable;

  protected:
    Game::Stance::Type	_stance;
    Game::Ressources	_carrying;
    unsigned int	_xp;
    unsigned int	_level;
    const Kernel::Data	*_lvlData;
    Kernel::ID::id_t	_spot;

    virtual void	setXP(unsigned int);
    virtual void	setLevel(unsigned int);

    virtual unsigned int	getUIntFromData(void *) const;
    virtual double		getDoubleFromData(void *) const;

  public:
    Unit(void);
    virtual ~Unit(void);

    void	init(unsigned int, const std::string &, const Game::Player *, int, double, double, double,
		     Game::Type type = Game::UNIT);
    Game::Stance::Type	getStance(void) const;
    virtual void	setStance(Game::Stance::Type);
    virtual void	addRessources(Game::Ressources::Type, int);
    const Game::Ressources	&getRessources(void) const;
    unsigned int	getRessources(Game::Ressources::Type) const;
    virtual void	setRessources(Game::Ressources::Type, unsigned int);
    virtual void	removeRessources(Game::Ressources::Type, int);

    unsigned int	getXP(void) const;
    unsigned int	getLevel(void) const;

    void		setXPLevel(unsigned int, unsigned int);

    virtual void	addXP(unsigned int);

    Kernel::ID::id_t getSpot(void) const;

    void		setSpot(Kernel::ID::id_t);

    virtual void	destroy(void);

  };

}

#endif
