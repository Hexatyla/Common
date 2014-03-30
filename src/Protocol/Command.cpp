//
// Command.cpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 24 16:22:42 2014 gautier lefebvre
// Last update Mon Mar 24 19:18:54 2014 geoffrey bauduin
//

#include	"Utils/Undefined.hpp"
#include	"Protocol/Command.hpp"
#include	"Converter.hpp"

const std::string	Command::CommandToString(::Command::Command c) {
  for (int i = 0 ; i < ::Command::NB_COMMAND ; ++i) {
    if (CommandStringTab[i].command == c) {
      return (CommandStringTab[i].string);
    }
  }
  return (std::string("undefined ") + Converter::StringOf<::Command::Command>(c));
}
