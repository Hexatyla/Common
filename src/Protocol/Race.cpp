//
// Race.cpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 24 16:09:10 2014 gautier lefebvre
// Last update Wed Mar 26 15:48:40 2014 Gautier Lefebvre
//

#include	"Utils/Undefined.hpp"
#include	"Protocol/Race.hpp"

const std::string &Race::RaceToString(::Race::Race r) {
  for (int i = 0 ; i < ::Race::NB_RACE ; ++i) {
    if (RaceStringTab[i].race == r) {
      return (RaceStringTab[i].string);
    }
  }
  return (undefined);
}

::Race::Race Race::RaceOfString(const std::string & r) {
  for (int i = 0 ; i < ::Race::NB_RACE ; ++i) {
    if (RaceStringTab[i].string == r) {
      return (RaceStringTab[i].race);
    }
  }
  return (::Race::RANDOM);
}
