//
// CapacityData.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 17 15:03:54 2014 geoffrey bauduin
// Last update Fri Mar 14 16:11:20 2014 geoffrey bauduin
//

#ifndef KERNEL_CAPACITYDATA_HPP_
# define KERNEL_CAPACITYDATA_HPP_

#include	<list>
#include	"Kernel/Serial.hpp"
#include	"IFromFactory.hpp"
#include	"Game/Capacity.hpp"

namespace	Kernel {

  class	CapacityData: virtual public IFromFactory {

  public:
    Game::Capacity::Target	target;
    std::vector<Kernel::Serial>	projectiles;
    std::vector<Kernel::Serial>	effects;
    bool			canAuto;
    bool			isAuto;
    bool			passive;

    CapacityData(void);
    virtual ~CapacityData(void);

    void	init(bool, bool, bool);
    virtual void destroy(void);

  };

}

#endif
