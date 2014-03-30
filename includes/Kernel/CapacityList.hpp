//
// CapacityList.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Thu Jan 16 17:38:36 2014 geoffrey bauduin
// Last update Fri Mar 14 16:13:30 2014 geoffrey bauduin
//

#ifndef KERNEL_CAPACITYLIST_HPP_
# define KERNEL_CAPACITYLIST_HPP_

#include	<vector>
#include	<string>
#include	"Kernel/Serial.hpp"
#include	"IFromFactory.hpp"

namespace	Kernel {

  class	CapacityList: virtual public IFromFactory {

  public:
    std::vector<Kernel::Serial>	list;

    CapacityList(void);
    virtual ~CapacityList(void);

    void	init(void);
    virtual void	destroy(void);

  };

}

#endif
