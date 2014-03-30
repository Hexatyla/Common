//
// Color.cpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 24 15:10:30 2014 gautier lefebvre
// Last update Fri Jan 24 16:23:08 2014 gautier lefebvre
//

#include	"Utils/Undefined.hpp"
#include	"Protocol/Color.hpp"

const std::string&	Color::ColorToString(::Color::Color c) {
  for (int i = 0 ; i < ::Color::NB_COLOR ; ++i) {
    if (ColorStringTab[i].color == c) {
      return (ColorStringTab[i].string);
    }
  }
  return (undefined);
}
