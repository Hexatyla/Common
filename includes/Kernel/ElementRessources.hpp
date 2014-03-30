//
// ElementRessources.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sun Jan 12 14:07:35 2014 geoffrey bauduin
// Last update Tue Mar 18 13:52:25 2014 geoffrey bauduin
//

#ifndef KERNEL_ELEMENT_RESSOURCES_HPP_
# define KERNEL_ELEMENT_RESSOURCES_HPP_

#include	"IFromFactory.hpp"
#include	"Threading/Mutex.hpp"

namespace	Kernel {

  class	ElementRessources: virtual public IFromFactory {

  public:
    enum Type {
      NONE,
      ENERGY,
      MANA,
      RAGE
    };

  protected:
    mutable Mutex	*_mutex;
    Type		_type;
    unsigned int	_life;
    unsigned int	_maxLife;
    unsigned int	_ress;
    unsigned int	_maxRess;

    void	change(unsigned int *, unsigned int, int);

  public:
    ElementRessources(void);
    virtual ~ElementRessources(void);

    void		init(unsigned int, Type, unsigned int, unsigned int, unsigned int);
    virtual void destroy(void);

    unsigned int	getLife(void) const;
    unsigned int	getRessource(void) const;
    Type		getRessourceType(void) const;
    void		changeLife(int);
    void		changeRessource(int);
    bool		hasEnough(const Kernel::ElementRessources &) const;
    void		setLife(unsigned int);
    void		setRessources(unsigned int);

  };

}

#endif
