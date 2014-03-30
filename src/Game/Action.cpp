//
// Action.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sun Feb 16 15:05:43 2014 geoffrey bauduin
// Last update Sun Feb 16 16:06:46 2014 geoffrey bauduin
//

#include	"Game/Action.hpp"

Game::Action::Action(void):
  _type(ACTION_NONE) {

}

Game::Action::~Action(void) {

}

void	Game::Action::init(Game::eAction type) {
  this->_type = type;
}

void	Game::Action::destroy(void) {

}

Game::eAction	Game::Action::getType(void) const {
  return (this->_type);
}
