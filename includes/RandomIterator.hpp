//
// RandomIterator.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Tue Mar 11 16:06:25 2014 geoffrey bauduin
// Last update Tue Mar 11 16:06:51 2014 geoffrey bauduin
//

#ifndef RANDOM_ITERATOR_HPP_
# define RANDOM_ITERATOR_HPP_

#include	<algorithm>

template<typename T>
static typename T::iterator random_iterator(T &stl_container) {
  typename T::iterator it = stl_container.begin();
  std::advance(it, rand() % stl_container.size());
  return (it);
}

#endif
