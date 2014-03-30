//
// Factory.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Jan 21 14:45:26 2014 geoffrey bauduin
// Last update Thu Jan 23 13:38:26 2014 geoffrey bauduin
//

#ifndef FACTORY_HPP_
# define FACTORY_HPP_

#include	"Clock.hpp"

namespace	Factory {

  void	init(void);
  void	end(void);

  class	Clock {

  public:
    static ::Clock	*create(void);
    static void		remove(::Clock *);

  };

}

#endif
