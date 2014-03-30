//
// DoubleAccessContainer.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sat Feb  1 21:05:00 2014 geoffrey bauduin
// Last update Sat Mar 15 22:05:36 2014 geoffrey bauduin
//

#ifndef DOUBLE_ACCESS_CONTAINER_HPP_
# define DOUBLE_ACCESS_CONTAINER_HPP_

#include	<map>
#include	<list>
#include	"Threading/ScopeLock.hpp"

template<class C, class D>
class	DoubleAccessContainer {

private:
  std::map<C, std::list<D> >	_mapCD;
  std::map<D, C>		_mapDC;
  mutable Mutex			*_mutex;

public:
  DoubleAccessContainer(void): _mapCD(), _mapDC(), _mutex(new Mutex) {}
  virtual ~DoubleAccessContainer(void) {
    delete this->_mutex;
  }

  const std::list<D>	&at(C c) const {
    ScopeLock s(this->_mutex);
    return (this->_mapCD.at(c));
  }

  C			at(D d) const {
    ScopeLock s(this->_mutex);
    return (this->_mapDC.at(d));
  }

  const std::list<D>	operator[](C c) {
    ScopeLock s(this->_mutex);
    return (this->_mapCD[c]);
  }

  C			operator[](D d) {
    ScopeLock s(this->_mutex);
    return (this->_mapDC[d]);
  }

  void	push(C c, D d) {
    ScopeLock s(this->_mutex);
    this->_mapCD[c].push_back(d);
    this->_mapDC[d] = c;
  }

  void	remove(C c) {
    ScopeLock s(this->_mutex);
    // Remove all players contained in C
    for (auto it : this->_mapCD[c]) {
      this->_mapDC.erase(it);
    }
    this->_mapCD.erase(c);
  }

  void	remove(D d) {
    ScopeLock s(this->_mutex);
    this->_mapCD[this->_mapDC[d]].remove(d);
    this->_mapDC.remove(d);
  }

  const std::map<C, std::list<D> > &getFirstMap(void) const {
    return (this->_mapCD);
  }

  const std::map<D, C> &getSecondMap(void) const {
    return (this->_mapDC);
  }

};

#endif
