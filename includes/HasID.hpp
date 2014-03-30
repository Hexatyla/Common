//
// HasID.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Mon Jan 20 10:44:54 2014 geoffrey bauduin
// Last update Wed Feb 12 17:15:33 2014 geoffrey bauduin
//

#ifndef HASID_HPP_
# define HASID_HPP_

#include	"Kernel/ID.hpp"
#include	"IFromFactory.hpp"

class	HasID: virtual public IFromFactory {

protected:
  Kernel::ID::id_t	_id;

public:
  HasID(void);
  virtual ~HasID(void);

  void			init(Kernel::ID::id_t);
  virtual void	destroy(void);
  Kernel::ID::id_t	getID(void) const;

};

#endif
