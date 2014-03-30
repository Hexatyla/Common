//
// Position.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 17:13:05 2014 geoffrey bauduin
// Last update Wed Feb 19 00:05:00 2014 geoffrey bauduin
//

#include	"Game/Position.hpp"

Game::Position::Position(void):
  _position(0.0, 0.0, 0.0), _orientation(0) {

}

Game::Position::~Position(void) {}

void	Game::Position::destroy(void) {

}

void	Game::Position::init(int orientation, double x, double y, double z) {
  this->_position.x = x;
  this->_position.y = y;
  this->_position.z = z;
  this->_orientation = orientation;
}

double	Game::Position::getX(void) const {
  return (this->_position.x);
}

double	Game::Position::getY(void) const {
  return (this->_position.y);
}

double	Game::Position::getZ(void) const {
  return (this->_position.z);
}

int	Game::Position::getOrientation(void) const {
  return (this->_orientation);
}

const Vector3d	&Game::Position::getPosition(void) const {
  return (this->_position);
}
