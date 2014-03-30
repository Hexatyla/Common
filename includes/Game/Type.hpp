//
// Type.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 17 16:43:40 2014 geoffrey bauduin
// Last update Fri Mar 14 16:35:15 2014 geoffrey bauduin
//

#ifndef GAME_TYPE_HPP_
# define GAME_TYPE_HPP_

#define	TYPE_NBR	9

namespace	Game {

  enum	Type {
    NONE =		0b0000000000,
    CAPACITY =		0b0000000001,
    EFFECT =		0b0000000010,
    BUILDING =		0b0000000100,
    AMELIORATION =	0b0000001000,
    UNIT =		0b0000010000,
    HERO =		0b0000100000,
    PROJECTILE =	0b0001000000,
    OBJECT =		0b0010000000,
    RESSSPOT =		0b0100000000,
    SPELLS =            0b1000000000,
    ALL_T =             0b1111111111
  };

}

#define	MOVABLE_OBJECTS	(::Game::UNIT | ::Game::HERO | ::Game::PROJECTILE)

#endif
