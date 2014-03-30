//
// Factory.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 15:55:16 2014 geoffrey bauduin
// Last update Tue Feb  4 18:01:51 2014 geoffrey bauduin
//

#ifndef FACTORY_KERNEL_HPP_
# define FACTORY_KERNEL_HPP_

#include	"Kernel/Data.hpp"
#include	"Kernel/ElementRessources.hpp"
#include	"Kernel/Cost.hpp"
#include	"Kernel/Time.hpp"
#include	"Kernel/CapacityList.hpp"
#include	"Kernel/CapacityData.hpp"
#include	"Kernel/BuildingData.hpp"
#include	"Kernel/Effect.hpp"

namespace	Factory {

  namespace	Kernel {


    void	init(void);
    void	end(void);

    class	Data {

    public:
      static ::Kernel::Data	*create(::Game::Type type, 
					const std::string &name, const std::string &serial, unsigned int attack,
					unsigned int defense, unsigned int hpRegen, unsigned int speed,
					double critChance, unsigned int maxHP, double hitbox, double attackRange,
					int passthrough, ::Kernel::ElementRessources::Type typeRessources,
					unsigned int maxRessources, unsigned int ressourcesRegen, double sightD, double sightN);
      static void		remove(::Kernel::Data *);

    };

    class	Cost {

    public:
      static ::Kernel::Cost		*create(unsigned int, unsigned int, unsigned int,
						::Kernel::ElementRessources::Type, unsigned int, unsigned int);
      static void			remove(::Kernel::Cost *);

    };

    class	Time {

    public:
      static ::Kernel::Time		*create(double, double, double, double, ::Kernel::Time::Canalisation when = ::Kernel::Time::NONE);
      static void			remove(::Kernel::Time *);

    };

    class	CapacityList {

    public:
      static ::Kernel::CapacityList	*create(void);
      static void			remove(::Kernel::CapacityList *);

    };

    class	CapacityData {

    public:
      static ::Kernel::CapacityData	*create(bool, bool, bool passive = false);
      static void			remove(::Kernel::CapacityData *);

    };

    class	BuildingData {

    public:
      static ::Kernel::BuildingData	*create(void);
      static void			remove(::Kernel::BuildingData *);

    };

    class	Effect {

    public:
      static ::Kernel::Effect	*create(::Kernel::Effect::Type, ::Kernel::Effect::TargetSide, ::Game::Type);
      static void		remove(::Kernel::Effect *);

    };

  }

}

#endif
