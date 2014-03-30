//
// Team.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 17 15:46:52 2014 geoffrey bauduin
// Last update Sun Mar  9 00:46:36 2014 geoffrey bauduin
//

#ifndef GAME_TEAM_HPP_
# define GAME_TEAM_HPP_

#include	<list>
#include	"Game/Player.hpp"
#include	"IFromFactory.hpp"

namespace	Game {

  class	Team: virtual public IFromFactory {

  protected:
    std::list<const Game::Player *>	_players;
    int					_nb;

  public:
    Team(void);
    virtual ~Team(void);

    void	init(void);
    virtual void	destroy(void);

    void	addPlayer(const Game::Player *);
    void	removePlayer(const Game::Player *);
    bool	isInTeam(const Game::Player *) const;
    int		getNb() const;
    void	setNb(int);
    bool	operator==(int) const;

  };

}

#endif
