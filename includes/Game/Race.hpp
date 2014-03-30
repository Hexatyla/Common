//
// Race.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 18:38:12 2014 geoffrey bauduin
// Last update Thu Mar 13 14:25:20 2014 geoffrey bauduin
//

#ifndef GAME_RACE_HPP_
# define GAME_RACE_HPP_

#include	<string>
#include	<map>
#include	<vector>
#include	"HasSerial.hpp"
#include	"Game/Amelioration.hpp"
#include	"Game/Building.hpp"
#include	"Game/Hero.hpp"
#include	"Game/Unit.hpp"
#include	"Game/Requirements.hpp"
#include	"Kernel/Serial.hpp"
#include	"IFromFactory.hpp"

namespace	Game {

  class	Race: public HasSerial, virtual public IFromFactory {

  protected:
    std::map<Kernel::Serial, Game::Requirements *>		_ameliorations;
    std::map<Kernel::Serial, Game::Requirements *>		_buildings;
    std::map<Kernel::Serial, Game::Requirements *>		_units;
    std::map<Kernel::Serial, Game::Requirements *>		_heroes;

    std::vector<Kernel::Serial>	_vUnits;
    std::vector<Kernel::Serial> _vBuildings;
    std::vector<Kernel::Serial> _vHeroes;
    std::vector<Kernel::Serial> _vAmeliorations;

    std::string						_name;

  private:
    std::vector<std::map<Kernel::Serial, Game::Requirements *> *>	_maps;

    bool	find(const std::vector<Kernel::Serial> &, const Kernel::Serial &) const;

  public:
    Race(void);
    virtual ~Race(void);

    void	init(const std::string &, const Kernel::Serial &);
    virtual void	destroy(void);

    void	addBuilding(const Kernel::Serial &, Game::Requirements *);
    void	addUnit(const Kernel::Serial &, Game::Requirements *);
    void	addHero(const Kernel::Serial &, Game::Requirements *);
    void	addAmelioration(const Kernel::Serial &, Game::Requirements *);

    const std::string &getName(void) const;

    const std::vector<Kernel::Serial>	&getUnits(void) const;
    const std::vector<Kernel::Serial>	&getBuildings(void) const;
    const std::vector<Kernel::Serial>	&getHeroes(void) const;
    const std::vector<Kernel::Serial>	&getAmeliorations(void) const;

    bool	hasUnit(const Kernel::Serial &) const;
    bool	hasBuilding(const Kernel::Serial &) const;
    bool	hasHero(const Kernel::Serial &) const;
    bool	hasAmelioration(const Kernel::Serial &) const;

    bool	hasUnitNamed(const std::string &) const;

    const Game::Requirements *getUnitRequirements(const Kernel::Serial &) const;
    const Game::Requirements *getBuildingRequirements(const Kernel::Serial &) const;
    const Game::Requirements *getHeroRequirements(const Kernel::Serial &) const;
    const Game::Requirements *getAmeliorationRequirements(const Kernel::Serial &) const;

    bool	hasItem(const Kernel::Serial &, ::Game::Type) const;

    void	setRequirements(const Kernel::Serial &, Game::Requirements *);

    void	refreshSerial(void);

    void	dump(void) const;

  };

}

#endif
