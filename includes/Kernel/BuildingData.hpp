//
// BuildingData.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 17 16:30:48 2014 geoffrey bauduin
// Last update Fri Mar 14 16:15:34 2014 geoffrey bauduin
//

#ifndef KERNEL_BUILDINGDATA_HPP_
# define KERNEL_BUILDINGDATA_HPP_

#include	<vector>
#include	"Kernel/Serial.hpp"
#include	"IFromFactory.hpp"

namespace	Kernel {

  class	BuildingData: public IFromFactory {

  public:
    std::vector<Kernel::Serial>	units;

    BuildingData(void);
    virtual ~BuildingData(void);

    void	init(void);
    virtual void destroy(void);

  };

}

#endif
