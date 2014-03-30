//
// RessourcesSpot.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Mon Feb 10 11:59:32 2014 geoffrey bauduin
// Last update Tue Mar 25 11:40:24 2014 geoffrey bauduin
//

#ifndef GAME_RESSOURCES_SPOT_HPP_
# define GAME_RESSOURCES_SPOT_HPP_

#include	<list>
#include	"Game/Ressources.hpp"
#include	"Game/AElement.hpp"
#include	"Threading/Mutex.hpp"
#include	"IFromFactory.hpp"

namespace	Game {

  class	RessourcesSpot: virtual public ::Game::AElement, virtual public IFromFactory {

  protected:
    Game::Ressources::Type	_type;
    Game::Ressources		_capacity;
    std::list<Kernel::ID::id_t>	_harvesters;

  private:
    mutable Mutex		*_mutex;

  public:
    RessourcesSpot(void);
    virtual ~RessourcesSpot(void);


    void	init(Kernel::ID::id_t, double, double, double, Game::Ressources::Type,
		     unsigned int amount = 0);
    virtual void	destroy(void);

    virtual void	addHarvester(Kernel::ID::id_t, unsigned int amount = 0);
    virtual void	removeHarvester(Kernel::ID::id_t);
    const std::list<Kernel::ID::id_t> &getHarvesters(void) const;
    bool		canBeHarvested(void) const;
    bool		isHarvesting(Kernel::ID::id_t) const;
    Game::Ressources::Type	getSpotType(void) const;

    void	setAmount(unsigned int);

    unsigned int	getAmount(void) const;

  };

}

#endif
