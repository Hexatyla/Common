//
// Amelioration.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 17:36:35 2014 geoffrey bauduin
// Last update Wed Feb 12 17:18:52 2014 geoffrey bauduin
//

#ifndef GAME_AMELIORATION_HPP_
# define GAME_AMELIORATION_HPP_

#include	"HasSerial.hpp"
#include	"HasInfos.hpp"
#include	"IFromFactory.hpp"

namespace	Game {

  class	Amelioration: public HasSerial, public HasInfos, virtual public IFromFactory {

  private:
    Kernel::Serial	_owner;

  public:
    Amelioration(void);
    virtual ~Amelioration(void);

    void	init(const Kernel::Serial &, const Kernel::Serial &);
    const Kernel::Serial &appliesTo(void) const;
    virtual void	destroy(void);

  };

}

#endif
