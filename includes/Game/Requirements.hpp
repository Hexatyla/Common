//
// Requirements.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 18:55:29 2014 geoffrey bauduin
// Last update Tue Mar 25 13:42:22 2014 geoffrey bauduin
//

#ifndef	GAME_REQUIREMENTS_HPP_
# define GAME_REQUIREMENTS_HPP_

#include	<vector>
#include	<map>
#include	"IFromFactory.hpp"
#include	"Kernel/Serial.hpp"
#include	"Threading/Mutex.hpp"

namespace	Game {

  class Player;

  class	Requirements: virtual public IFromFactory {

  private:
    mutable Mutex		*_mutex;
    std::vector<Kernel::Serial>	_buildings;
    std::vector<Kernel::Serial>	_ameliorations;

  public:
    Requirements(void);
    virtual ~Requirements(void);

    void	init(void);
    virtual void	destroy(void);

    void	addBuilding(const Kernel::Serial &);
    void	addAmelioration(const Kernel::Serial &);

    const std::vector<Kernel::Serial>	&getBuildings(void) const;
    const std::vector<Kernel::Serial>	&getAmeliorations(void) const;

    bool	fullfilledByPlayer(const Game::Player *) const;

    const std::map<Kernel::Serial, bool>	getFullfilledData(const Game::Player *) const;

    void	dump(void) const;

  };

}

#endif
