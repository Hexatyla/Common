//
// Difficulty.cpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 24 16:33:52 2014 gautier lefebvre
// Last update Fri Jan 24 16:36:56 2014 gautier lefebvre
//

#include	"Utils/Undefined.hpp"
#include	"Protocol/Difficulty.hpp"

const std::string&	Difficulty::DifficultyToString(::Difficulty::Difficulty c) {
  for (int i = 0 ; i < ::Difficulty::NB_DIFFICULTY ; ++i) {
    if (DifficultyStringTab[i].difficulty == c) {
      return (DifficultyStringTab[i].string);
    }
  }
  return (undefined);
}
