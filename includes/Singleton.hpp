//
// Singleton.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sun Jan 12 14:32:35 2014 geoffrey bauduin
// Last update Tue Mar  4 17:40:58 2014 geoffrey bauduin
//

#ifndef	SINGLETON_HPP_
# define SINGLETON_HPP_

#include	<cstddef>

template<class T>
class	Singleton {

private:
  static T	*_instance;

  static void	createInstance(void) { _instance = new T; }

public:
  Singleton(void) {}
  virtual ~Singleton(void) {}

  static T	*getInstance(void) {
    if (_instance == NULL) {
      createInstance();
    }
    return _instance;
  }

  static void	deleteInstance(void) { delete _instance; }

};

template<class T>
T *Singleton<T>::_instance = NULL;

#endif
