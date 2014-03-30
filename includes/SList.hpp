//
// SList.hpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Tue Jan 21 13:39:08 2014 gautier lefebvre
// Last update Tue Jan 21 13:40:28 2014 gautier lefebvre
//

#ifndef		__SLIST_HPP__
#define		__SLIST_HPP__

#include	<list>
#include	"Threading/Mutex.hpp"

template<typename T>
class		SList :public Mutex, public std::list<T> {
public:
  SList():
    Mutex::Mutex(),
    std::list<T>() {}

  virtual ~SList() {}
};

#endif
