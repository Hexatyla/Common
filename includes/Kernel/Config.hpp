//
// Config.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Feb 25 21:39:42 2014 geoffrey bauduin
// Last update Tue Mar 25 10:03:27 2014 geoffrey bauduin
//

#ifndef KERNEL_CONFIG_HPP_
# define KERNEL_CONFIG_HPP_

#include	<set>
#include	<map>
#include	<string>
#include	"Singleton.hpp"

namespace	Kernel {

  class	Config: public Singleton<Kernel::Config> {

    friend class Singleton<Kernel::Config>;

  public:
    enum Parameter {
      HP_REGEN_TIMER,
      RESS_REGEN_TIMER,
      DAY_NIGHT_SWITCH_TIMER,
      BUILD_BUILDING_TIME_BETWEEN_TICKS,
      BUILD_BUILDERS_AMOUNT_PER_TICK,
      HARVEST_TIME_BETWEEN_TICKS,
      HARVEST_AMOUNT_PER_TICK,
      RESSOURCES_SPOT_DEFAULT_CAPACITY,
      MAX_HARVESTERS_ON_SPOT,
      HARVESTER_CAPACITY,
      UPDATES_PER_SECOND,
      BASE_DELAY_BETWEEN_ATTACKS,
      CRIT_CHANCE_MULTIPLIER,
      MOVE_TEST_NUMBER,
      BUILD_CAPACITY,
      CARRY_RESSOURCES_CAPACITY,
      HARVEST_CAPACITY,
      RECOVER_GOLD_CAPACITY,
      RECOVER_WOOD_CAPACITY,
      HERO_OBJECTS_NUMBER,
      PATROL_CAPACITY,
      UPDATE_ITEM_MAX_ELAPSED_TIME,
      START_WOOD,
      START_GOLD,
      START_FOOD,
      START_UNIT,
      XP_BUILDING,
      XP_UNIT,
      TIMER_OUT_OF_COMBAT,
      GOLD_SPOT_SERIAL,
      WOOD_SPOT_SERIAL,
      SPEC_DELAY,
      MAP_PRECISION,
      MISS_CHANCE
    };

  private:
    enum Type {
      DOUBLE,
      STRING
    };

    struct data {
      Type		type;
      double		d;
      const char	*s;
    };

    std::map<Parameter, std::string>	_pstrings;
    std::map<Parameter, double>		_pdoubles;

    std::map<std::string, Parameter>	_hashtab;
    std::map<Parameter, data>		_pTypes;

    std::string	_dflt;

    Config(void);
    virtual ~Config(void);

    void	parseFile(const std::string &);

  public:
    double		getDouble(Parameter) const;
    const std::string	&getString(Parameter) const;
    unsigned int	getUInt(Parameter) const;

  };

}

#endif
