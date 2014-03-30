//
// Race.hpp for ex in /home/deleme/pfa/includes
// 
// Made by anthony delemer
// Login   <deleme_a@epitech.net>
// 
// Started on  Mon Jan 13 14:52:09 2014 anthony delemer
// Last update Wed Mar 26 15:48:17 2014 Gautier Lefebvre
//

#ifndef		__RACE_HPP__
# define	__RACE_HPP__

#include	<string>

namespace	Race {
  enum	Race {
    GENICIA,
    HUMANOIDE,
    IMPERIUM,
    RANDOM
  };

  const std::string &RaceToString(::Race::Race r);
  ::Race::Race	     RaceOfString(const std::string &);

  struct RaceString {
    ::Race::Race	race;
    std::string		string;
  };

  static const int	NB_RACE = 4;

  static const RaceString RaceStringTab[::Race::NB_RACE]={
    {Race::GENICIA, "GENICIA"},
    {Race::HUMANOIDE, "HUMANOIDE"},
    {Race::IMPERIUM, "IMPERIUM"},
    {Race::RANDOM, "Random"}
  };
}

#endif
