//
// Color.hpp for ex in /home/deleme/pfa/includes/enum
// 
// Made by anthony delemer
// Login   <deleme_a@epitech.net>
// 
// Started on  Mon Jan 13 14:34:58 2014 anthony delemer
// Last update Sat Mar 15 14:01:50 2014 gautier lefebvre
//

#ifndef		__COLOR_HPP__
# define	__COLOR_HPP__

#include	<string>

namespace	Color {
  enum Color {
    RANDOM,
    RED,
    BLUE,
    GREEN,
    ORANGE,
    SKYBLUE,
    CYAN,
    ROSE,
    SILVER
  };

  const std::string& ColorToString(::Color::Color c);

  struct	ColorString {
    ::Color::Color	color;
    std::string		string;
  };

  static const int	NB_COLOR = 9;

  static const ColorString ColorStringTab[::Color::NB_COLOR]={
    {Color::RANDOM, "Random"},
    {Color::RED, "Red"},
    {Color::BLUE, "Blue"},
    {Color::GREEN, "Green"},
    {Color::SKYBLUE, "Skyblue"},
    {Color::SILVER, "Silver"},
    {Color::ORANGE, "Orange"},
    {Color::ROSE, "Rose"},
    {Color::CYAN, "Cyan"}
  };
}

#endif
