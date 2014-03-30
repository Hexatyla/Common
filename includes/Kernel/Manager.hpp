//
// Manager.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sun Jan 12 14:36:14 2014 geoffrey bauduin
// Last update Fri Mar 14 15:52:17 2014 geoffrey bauduin
//

#ifndef	KERNEL_MANAGER_HPP_
# define KERNEL_MANAGER_HPP_

#include	<map>
#include	<string>
#include	"Singleton.hpp"
#include	"Kernel/Data.hpp"
#include	"Kernel/Cost.hpp"
#include	"Kernel/Time.hpp"
#include	"Kernel/CapacityList.hpp"
#include	"Kernel/Serial.hpp"
#include	"Kernel/CapacityData.hpp"
#include	"Kernel/BuildingData.hpp"
#include	"Kernel/Effect.hpp"
#include	"Game/Race.hpp"

namespace	Kernel {

  class	Manager: public Singleton<Kernel::Manager> {

    friend class Singleton;

  private:
    std::map<Kernel::Serial, Kernel::Data *>		_datas;
    std::map<Kernel::Serial, Kernel::Cost *>		_costs;
    std::map<Kernel::Serial, Kernel::Time *>		_timers;
    std::map<Kernel::Serial, Kernel::CapacityList *>	_capacityList;
    std::map<Kernel::Serial, Kernel::CapacityData *>	_capacityData;
    std::map<Kernel::Serial, Kernel::BuildingData *>	_buildingData;
    std::map<Kernel::Serial, Kernel::Effect *>		_effects;

    Manager(void);
    virtual ~Manager(void);

  public:
    void				loadRace(const Kernel::Serial &);
    void				deleteRace(const Game::Race *);
    const Kernel::Data			*getData(const Kernel::Serial &) const;
    void				addData(const Kernel::Serial &, Kernel::Data *);
    const Kernel::Cost			*getCost(const Kernel::Serial &) const;
    void				addCost(const Kernel::Serial &, Kernel::Cost *);
    const Kernel::Time			*getTimer(const Kernel::Serial &) const;
    void				addTimer(const Kernel::Serial &, Kernel::Time *);
    const Kernel::CapacityList		*getCapacityList(const Kernel::Serial &) const;
    void				addCapacityList(const Kernel::Serial &, Kernel::CapacityList *);
    const Kernel::CapacityData		*getCapacityData(const Kernel::Serial &) const;
    void				addCapacityData(const Kernel::Serial &, Kernel::CapacityData *);
    const Kernel::BuildingData		*getBuildingData(const Kernel::Serial &) const;
    void				addBuildingData(const Kernel::Serial &, Kernel::BuildingData *);
    void				addEffect(const Kernel::Serial &, Kernel::Effect *);
    const Kernel::Effect		*getEffect(const Kernel::Serial &) const;

    void	init(void);

  };

}

#endif
