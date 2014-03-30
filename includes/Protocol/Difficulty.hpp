//
// Difficulty.hpp for ex in /home/deleme/pfa/includes
// 
// Made by anthony delemer
// Login   <deleme_a@epitech.net>
// 
// Started on  Mon Jan 13 14:53:33 2014 anthony delemer
// Last update Fri Jan 24 16:33:36 2014 gautier lefebvre
//

#ifndef		__DIFFICULTY_HPP__
# define	__DIFFICULTY_HPP__

#include	<string>

namespace	Difficulty {
  enum	Difficulty	{
    EASY,
    NORMAL,
    HARD
  };

  const std::string &DifficultyToString(::Difficulty::Difficulty d);

  struct DifficultyString {
    ::Difficulty::Difficulty difficulty;
    std::string		string;
  };

  static const int	NB_DIFFICULTY = 3;

  static const DifficultyString DifficultyStringTab[::Difficulty::NB_DIFFICULTY]={
    {::Difficulty::EASY, "Easy"},
    {::Difficulty::NORMAL, "Normal"},
    {::Difficulty::HARD, "Hard"}
  };
}

#endif
