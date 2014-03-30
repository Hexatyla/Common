//
// User.cpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Sun Feb  9 16:55:19 2014 gautier lefebvre
// Last update Sun Feb  9 17:08:09 2014 gautier lefebvre
//

#include	"Utils/Undefined.hpp"
#include	"Protocol/User.hpp"

const std::string&      ::User::StatusToString(::User::Status s) {
  for (int i = 0 ; i < ::User::NB_STATUS ; ++i) {
    if (::User::UserStatusStringTab[i].status == s) {
      return (::User::UserStatusStringTab[i].string);
    }
  }
  return (undefined);
}
