//
// HasInfos.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Wed Jan 15 14:20:15 2014 geoffrey bauduin
// Last update Fri Mar 14 16:03:33 2014 geoffrey bauduin
//

#ifndef HASINFOS_HPP_
# define HASINFOS_HPP_

#include	"Kernel/Data.hpp"
#include	"Kernel/ElementRessources.hpp"
#include	"Kernel/Cost.hpp"
#include	"Kernel/Time.hpp"
#include	"Kernel/BuildingData.hpp"
#include	"Game/Type.hpp"
#include	"Kernel/Effect.hpp"
#include	"IFromFactory.hpp"

namespace Kernel {
  class CapacityData;
}

class	HasInfos: virtual public IFromFactory {

public:
  struct infos {
    const Kernel::Data			*data;
    const Kernel::Cost			*cost;
    const Kernel::Time			*timer;
    const Kernel::CapacityData		*capacity;
    const Kernel::BuildingData		*building;
    const Kernel::Effect		*effect;
  };

protected:
  infos		_infos;

public:
  enum	Type {
    NONE         = 0b000000,
    DATA         = 0b000001,
    COST         = 0b000010,
    TIMER        = 0b000100,
    CAPACITYDATA = 0b001000,
    BUILDINGDATA = 0b010000,
    EFFECT	 = 0b100000,
    ALL          = 0b111111
  };

  static const std::map<Game::Type, int> _masks;
  static const std::map<Game::Type, int> initMasks(void);

public:
  HasInfos(void);
  virtual ~HasInfos(void);

  void	init(const Kernel::Serial &, Game::Type);
  virtual void	destroy(void);

  const infos &getInfos(void) const;

};

#endif
