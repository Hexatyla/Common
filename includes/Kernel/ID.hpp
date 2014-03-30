//
// ID.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Mon Jan 20 10:53:50 2014 geoffrey bauduin
// Last update Wed Mar  5 00:24:55 2014 geoffrey bauduin
//

#ifndef KERNEL_ID_HPP_
# define KERNEL_ID_HPP_

#include	<queue>
#include	<map>
#include	"Singleton.hpp"
#include	"Threading/Mutex.hpp"

namespace	Kernel {

  class	ID: public Singleton<Kernel::ID> {

    friend class Singleton;

  public:
    typedef unsigned int	id_t;

    enum Type {
      PLAYER,
      ITEM,
      GAME
    };

  private:
    struct data {
      std::queue<id_t>	pool;
      id_t		current;
      Mutex		*mutex;

      data(void): pool(), current(0), mutex(new Mutex) {}
      ~data(void) { delete mutex; }
    };

    std::map<Type, data *>	_data;

    ID(void);
    virtual ~ID(void);

    id_t	get(std::queue<id_t> &, id_t &);
    void	push(id_t, std::queue<id_t> &);

  public:
    id_t	get(Kernel::ID::Type);
    void	push(id_t, Kernel::ID::Type);

  };

}

#endif
