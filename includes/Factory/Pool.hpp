/*
** Pool.h for  in /home/geoffrey/Projects/pfa
** 
** Made by geoffrey bauduin
** Login   <baudui_g@epitech.net>
** 
** Started on  Tue Jan 21 14:43:22 2014 geoffrey bauduin
// Last update Thu Mar  6 11:51:59 2014 gautier lefebvre
*/

#ifndef FACTORY_POOL_HPP_
# define FACTORY_POOL_HPP_

#include	<queue>
#include <iostream>
#include	"Logger.hpp"
#include	"Threading/Mutex.hpp"
#include	"Threading/ScopeLock.hpp"

template<typename T>
class	Pool {

private:
  std::queue<T *>	_pool;
  unsigned int		_size;
  unsigned int		_bailout;
  Mutex			*_mutex;
  std::string		_name;

  void	bailout(bool reassign = false) {
    unsigned int size = reassign ? _bailout : _size;
    if (reassign) {
      Logger::getInstance()->logf("Bailing out the pool of %s", Logger::INFORMATION, &_name);
    }
    T *iw;
    for (unsigned int i = 0 ; i < size ; ++i) {
      iw = new T;
      //      std::cout << iw << std::endl;
      _pool.push(iw);
    }
  }

public:
  Pool(unsigned int size, unsigned int bailout, const std::string &name = "Object"):
    _pool(), _size(size), _bailout(bailout), _mutex(new Mutex), _name(name) {
    Logger::getInstance()->logf("\tInitializing pool of %s ...", Logger::INFORMATION, &_name);
    this->bailout();
  }

  ~Pool(void) {
    {
      ScopeLock s(this->_mutex);
      while (_pool.empty() == false) {
	delete _pool.front();
	_pool.pop();
      }
    }
    delete this->_mutex;
  }

  T	*get(void) {
    ScopeLock s(this->_mutex);
    if (_pool.empty() == true) {
      bailout(true);
    }
    T *item = _pool.front();
    _pool.pop();
    return (item);
  }

  void	push(T *item) {
    ScopeLock s(this->_mutex);
    _pool.push(item);
  }

};


#endif
