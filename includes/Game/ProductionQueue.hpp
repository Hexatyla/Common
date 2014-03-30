//
// ProductionQueue.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Thu Feb  6 13:37:38 2014 geoffrey bauduin
// Last update Fri Mar 21 13:58:35 2014 geoffrey bauduin
//

#ifndef GAME_PRODUCTION_QUEUE_HPP_
# define GAME_PRODUCTION_QUEUE_HPP_

#include	<deque>
#include	"Kernel/Serial.hpp"
#include	"Threading/Mutex.hpp"
#include	"IFromFactory.hpp"

namespace	Game {

  class	ProductionQueue: virtual public IFromFactory {

  private:
    std::deque<Kernel::Serial>	_queue;
    mutable Mutex		*_mutex;

  public:
    ProductionQueue(void);
    virtual ~ProductionQueue(void);

    void		init(void);
    virtual void	destroy(void);

    const Kernel::Serial	&front(void) const;
    const Kernel::Serial	&back(void) const;
    unsigned int		size(void) const;
    bool			empty(void) const;
    const Kernel::Serial	&at(unsigned int) const;
    bool			contains(const Kernel::Serial &) const;

    const std::deque<Kernel::Serial>	&getQueue(void) const;

    void	push(const Kernel::Serial &);
    void	insert(const Kernel::Serial &, unsigned int);
    bool	remove(const Kernel::Serial &);

    const Kernel::Serial	pop(void);

  };

}

#endif
