//
// Team.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 17 15:49:15 2014 geoffrey bauduin
// Last update Thu Feb 20 16:03:37 2014 gautier lefebvre
//

#include	<algorithm>
#include	"Game/Team.hpp"

Game::Team::Team(void):
  _players() {}

Game::Team::~Team(void) {}

void	Game::Team::init(void) {
}

void	Game::Team::addPlayer(const Game::Player *player) {
  this->_players.push_back(player);
}

void	Game::Team::removePlayer(const Game::Player *player) {
  this->_players.remove(player);
}

bool	Game::Team::isInTeam(const Game::Player *player) const {
  return (std::find(this->_players.begin(), this->_players.end(), player) != this->_players.end());
}

void	Game::Team::destroy(void) {
  this->_players.clear();
}

void	Game::Team::setNb(int n) { this->_nb = n; }
int	Game::Team::getNb() const { return (this->_nb); }
bool	Game::Team::operator==(int n) const { return (this->_nb == n); }
