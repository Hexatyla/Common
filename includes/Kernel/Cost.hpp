//
// Cost.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sun Jan 12 13:58:43 2014 geoffrey bauduin
// Last update Wed Feb 12 17:24:10 2014 geoffrey bauduin
//

#ifndef KERNEL_COST_HPP_
# define KERNEL_COST_HPP_

#include	<map>
#include	"Game/Ressources.hpp"
#include	"Kernel/ElementRessources.hpp"
#include	"IFromFactory.hpp"

namespace	Kernel {

  class	Cost: virtual public IFromFactory {

  public:
    Game::Ressources		ressources;
    Kernel::ElementRessources	personnalRessource;

    Cost(void);
    virtual ~Cost(void);

    void	init(unsigned int, unsigned int, unsigned int, Kernel::ElementRessources::Type, unsigned int, unsigned int);
    virtual void	destroy(void);
  };

}

#endif
