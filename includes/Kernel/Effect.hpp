//
// Effect.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Mon Feb  3 14:01:57 2014 geoffrey bauduin
// Last update Fri Mar 14 16:09:22 2014 geoffrey bauduin
//

#ifndef KERNEL_EFFECT_HPP_
# define KERNEL_EFFECT_HPP_

#include	<vector>
#include	"Game/Type.hpp"
#include	"IFromFactory.hpp"
#include	"Kernel/Serial.hpp"

namespace	Kernel {

  class	Effect: virtual public IFromFactory {

  public:
    enum	TargetSide {
      ALL = 0b11,
      ENEMY = 0b10,
      ALLY = 0b01
    };

    enum	Type {
      NONE,
      INVOCATION,
      STUN,
      TELEPORTING,
      AURA
    };

    Kernel::Effect::Type	type;
    Kernel::Effect::TargetSide	targetSide;
    Game::Type			targetType;
    std::vector<Kernel::Serial>	effects;

    Effect(void);
    ~Effect(void);

    void	init(Kernel::Effect::Type, Kernel::Effect::TargetSide, Game::Type);
    virtual void	destroy(void);

  };

}

#endif
