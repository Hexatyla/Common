//
// ABase.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Wed Feb 12 13:03:12 2014 geoffrey bauduin
// Last update Thu Mar 13 15:21:23 2014 geoffrey bauduin
//

#ifndef GAME_ABASE_HPP_
# define GAME_ABASE_HPP_

#include	"HasInfos.hpp"
#include	"HasSerial.hpp"
#include	"IFromFactory.hpp"
#include	"Threading/Mutex.hpp"

#define	GET_VAL(data, addr, type)	(reinterpret_cast<type *>(reinterpret_cast<unsigned long long>(data) + reinterpret_cast<unsigned long long>(addr)))

namespace	Game {
  class Player;
  class Race;
  class Team;

  class	ABase: public HasInfos, public HasSerial, virtual public IFromFactory {

  private:
    mutable Mutex		*_mutex;

  protected:
    const Game::Player	*_player;
    const Game::Race	*_race;
    Game::Type		_type;

    virtual unsigned int	getUIntFromData(void *addr) const;
    virtual double		getDoubleFromData(void *addr) const;

  public:
    ABase(void);
    virtual ~ABase(void);

    void	init(const Kernel::Serial &, Game::Type, const Game::Player *);
    virtual void	destroy(void);

    const Game::Player	*getPlayer(void) const;
    const Game::Race	*getRace(void) const;
    const Game::Team	*getTeam(void) const;
    Game::Type		getType(void) const;
    unsigned int	getMaxLife(void) const;
    unsigned int	getMaxRessources(void) const;
    virtual unsigned int	getAttack(void) const;
    unsigned int	getDefense(void) const;
    unsigned int	getHpRegen(void) const;
    virtual unsigned int	getSpeed(void) const;
    virtual double		getCritChance(void) const;
    double		getHitbox(void) const;
    double		getAttackRange(void) const;
    unsigned int	getRessourcesRegen(void) const;
    double		getDaySight(void) const;
    double		getNightSight(void) const;

  };

}

#endif
