//
// Building.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 18:10:20 2014 geoffrey bauduin
// Last update Mon Mar 24 17:07:34 2014 geoffrey bauduin
//

#ifndef GAME_BUILDING_HPP_
# define GAME_BUILDING_HPP_

#include	<list>
#include	"Game/AElement.hpp"
#include	"Threading/Mutex.hpp"
#include	"Game/ProductionQueue.hpp"
#include	"IFromFactory.hpp"
#include	"Game/CanUseCapacity.hpp"

namespace	Game {

  class	Building: virtual public Game::AElement, virtual IFromFactory, virtual public Game::CanUseCapacity {

  private:
    mutable Mutex		*_mutex;
    mutable Mutex		*_buildersMutex;

  protected:
    Game::ProductionQueue	_queue;
    std::list<Kernel::ID::id_t>	_builders;

  public:
    Building(void);
    virtual ~Building(void);

    void	init(unsigned int, const Kernel::Serial &, const Game::Player *, int, double, double, double);
    virtual void destroy(void);

    const Kernel::Serial	&frontQueue(void) const;
    const Kernel::Serial	&backQueue(void) const;

    const Game::ProductionQueue	*getProductionQueue(void) const;

    virtual void		addToQueue(const Kernel::Serial &);
    virtual void		placeInQueue(const Kernel::Serial &, unsigned int);
    virtual bool		removeFromQueue(const Kernel::Serial &);

    void			popQueue(void);

    virtual void		addBuilder(Kernel::ID::id_t);
    virtual void		removeBuilder(Kernel::ID::id_t);

    virtual void		setBuilt(void);

  };

}

#endif
