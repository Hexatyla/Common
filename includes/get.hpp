//
// get.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Mon Feb  3 16:43:33 2014 geoffrey bauduin
// Last update Mon Feb  3 16:47:23 2014 geoffrey bauduin
//

#ifndef GET_HPP_
# define GET_HPP_

#include	<stdexcept>

template<typename T>
static const T	*get(const Kernel::Serial &serial, const std::map<Kernel::Serial, T *> &data) {
  try {
    return (data.at(serial));
  }
  catch (std::out_of_range &e) {
    return (NULL);
  }
}

#endif
