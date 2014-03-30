//
// eAction.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sun Feb 16 15:48:25 2014 geoffrey bauduin
// Last update Mon Mar  3 17:02:25 2014 geoffrey bauduin
//

#ifndef GAME_EACTION_HPP_
# define GAME_EACTION_HPP_

namespace	Game {

  enum eAction {
    ACTION_PATROL,
    ACTION_BUILDING,
    ACTION_MOVE,
    ACTION_HARVEST,
    ACTION_RELEASE,
    ACTION_PICKUP,
    ACTION_START_BUILDING,
    ACTION_DEPOSIT,
    ACTION_START_HARVEST,
    ACTION_ATTACK,
    ACTION_FOLLOW,
    ACTION_PROJECTILE_FOLLOW,
    ACTION_PROJECTILE_MOVE,
    ACTION_START_CAPACITY,
    ACTION_CAST_CAPACITY,
    ACTION_NONE
  };

}

#endif
