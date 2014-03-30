//
// Data.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sun Jan 12 13:51:36 2014 geoffrey bauduin
// Last update Mon Mar 24 17:19:58 2014 geoffrey bauduin
//

#ifndef KERNEL_DATA_HPP_
# define KERNEL_DATA_HPP_

#include	<vector>
#include	<string>
#include	"Kernel/ElementRessources.hpp"
#include	"Game/Type.hpp"
#include	"IFromFactory.hpp"
#include	"Kernel/Serial.hpp"

namespace	Kernel {

  class	Data: virtual public IFromFactory {

  public:
    Game::Type				type;
    unsigned int			attack;
    unsigned int			defense;
    unsigned int			hpRegen;
    unsigned int			speed;
    double				critChance;
    unsigned int			maxHP;
    std::string				name;
    std::string				serial;
    double				hitbox;
    double				attackRange;
    int					passthrough;
    Kernel::ElementRessources::Type	typeRessources;
    unsigned int			maxRessources;
    unsigned int			ressourcesRegen;
    double				daySight;
    double				nightSight;
    std::vector<Kernel::Serial>		ameliorations;

#ifndef __SERVER__
    std::string	description;
    std::string	voice;
    std::string	voiceBirth;
    std::string	voiceDie;
    std::string	voiceAttack;
    std::string	icon;
    std::string	model;
#endif

  public:
    Data(void);
    virtual ~Data(void);

    void	init(Game::Type type,
		     const std::string &name, const std::string &serial, unsigned int attack,
		     unsigned int defense, unsigned int hpRegen, unsigned int speed,
		     double critChance, unsigned int maxHP, double hitbox, double attackRange,
		     int passthrough, Kernel::ElementRessources::Type typeRessources,
		     unsigned int maxRessources, unsigned int ressourcesRegen, double sightD, double sightN);
    virtual void	destroy(void);

  };

}

#endif
