//
// Ressources.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sun Jan 12 14:00:27 2014 geoffrey bauduin
// Last update Mon Mar 17 14:30:28 2014 geoffrey bauduin
//

#include	"Game/Ressources.hpp"
#include	"Threading/ScopeLock.hpp"

const std::map<Game::Ressources::Type, std::string>	Game::Ressources::_hashtab(Game::Ressources::initHashtab());

const std::map<Game::Ressources::Type, std::string>	Game::Ressources::initHashtab(void) {
  std::map<Type, std::string> htab;
  htab[GOLD] = "gold";
  htab[WOOD] = "wood";
  htab[FOOD] = "food";
  return (htab);
}

const std::string	&Game::Ressources::translate(Type t) {
  return (Game::Ressources::_hashtab.at(t));
}

Game::Ressources::Ressources(void):
  _mutex(new Mutex), _amount() {
  this->_amount[Game::Ressources::GOLD] = 0;
  this->_amount[Game::Ressources::WOOD] = 0;
  this->_amount[Game::Ressources::FOOD] = 0;
}

Game::Ressources::Ressources(const Game::Ressources &oth):
  _mutex(new Mutex), _amount(oth._amount) {

}

Game::Ressources::~Ressources(void) {
  delete this->_mutex;
}

Game::Ressources	&Game::Ressources::operator=(const Game::Ressources &rhs) {
  this->_amount = rhs._amount;
  return (*this);
}

void	Game::Ressources::init(unsigned int gold, unsigned int wood, unsigned int food) {
  this->_amount[Game::Ressources::GOLD] = static_cast<int>(gold);
  this->_amount[Game::Ressources::WOOD] = static_cast<int>(wood);
  this->_amount[Game::Ressources::FOOD] = static_cast<int>(food);
}

void	Game::Ressources::destroy(void) {
}

void	Game::Ressources::_set(Game::Ressources::Type type, int amount) {
  this->_amount[type] = amount;
}

void	Game::Ressources::set(Game::Ressources::Type type, unsigned int amount) {
  ScopeLock s(this->_mutex);
  this->_set(type, static_cast<int>(amount));
}

void	Game::Ressources::add(Game::Ressources::Type type, int amount) {
  ScopeLock s(this->_mutex);
  int newV = this->_amount[type] + amount;
  if (newV < 0 && type != FOOD) {
    this->_set(type, 0);
  }
  else {
    this->_set(type, newV);
  }
}

int	Game::Ressources::get(Game::Ressources::Type type) const {
  ScopeLock s(this->_mutex);
  return (this->_amount.at(type));
}

Game::Ressources	&Game::Ressources::operator+=(const Game::Ressources &rhs) {
  ScopeLock s(this->_mutex);
  for (auto it : rhs._amount) {
    this->_amount[it.first] += it.second;
  }
  return (*this);
}

Game::Ressources	&Game::Ressources::operator-=(const Game::Ressources &rhs) {
  ScopeLock s(this->_mutex);
  for (auto it : rhs._amount) {
    this->_amount[it.first] -= it.second;
  }
  return (*this);
}

bool	Game::Ressources::hasEnough(const Game::Ressources &rhs) const {
  ScopeLock s(this->_mutex);
  for (auto it : rhs._amount) {
    if (this->_amount.at(it.first) < it.second) {
      return (false);
    }
  }
  return (true);
}
