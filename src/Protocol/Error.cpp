//
// Error.cpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 10 17:11:46 2014 gautier lefebvre
// Last update Sun Feb  9 16:07:20 2014 gautier lefebvre
//

#include	"Utils/Undefined.hpp"
#include	"Protocol/Error.hpp"

const std::string &Error::CodeToString(Error::Code code) {
  for (int i = 0 ; i < NB_ERROR ; ++i) {
    if (Error::CodeStringTab[i].code == code) {
      return (Error::CodeStringTab[i].string);
    }
  }
  return (undefined);
}
