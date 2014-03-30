//
// Movable.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 17:16:04 2014 geoffrey bauduin
// Last update Thu Mar 13 17:35:23 2014 geoffrey bauduin
//

#include	"Game/Movable.hpp"
#include	"Threading/ScopeLock.hpp"

Game::Movable::Movable(void):
  Game::Position(),
  _mutex(new Mutex),
  _waypoints() {

}

Game::Movable::~Movable(void) {
  delete this->_mutex;
}

void	Game::Movable::init(int orientation, double x, double y, double z) {
  Game::Position::init(orientation, x, y, z);
}

void	Game::Movable::destroy(void) {
  Game::Position::destroy();
  this->_waypoints.clear();
}

void	Game::Movable::setX(double x) {
  this->_position.x = x;
}

void	Game::Movable::setY(double y) {
  this->_position.y = y;
}

void	Game::Movable::setZ(double z) {
  this->_position.z = z;
}

void	Game::Movable::setOrientation(int o) {
  this->_orientation = o;
}

void	Game::Movable::setPosition(double x, double y, double z) {
  ScopeLock s(this->_mutex);
  this->_position.x = x;
  this->_position.y = y;
  this->_position.z = z;
}

void	Game::Movable::setWaypoints(const std::vector<Vector3d> &waypoints) {
  ScopeLock s(this->_mutex);
  for (auto it : waypoints) {
    this->_waypoints.push_back(it);
  }
}

bool	Game::Movable::hasWaypoints(void) const {
  ScopeLock s(this->_mutex);
  return (!this->_waypoints.empty());
}

const std::deque<Vector3d> &Game::Movable::getWaypoints(void) const {
  ScopeLock s(this->_mutex);
  return (this->_waypoints);
}

const Vector3d	&Game::Movable::getFrontWaypoint(void) const {
  ScopeLock s(this->_mutex);
  return (this->_waypoints.front());
}

void	Game::Movable::popWaypoints(void) {
  ScopeLock s(this->_mutex);
  this->_waypoints.pop_front();
}

void	Game::Movable::clearWaypoints(void) {
  ScopeLock s(this->_mutex);
  this->_waypoints.clear();
}
