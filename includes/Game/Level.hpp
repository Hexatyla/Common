//
// Level.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Thu Mar  6 15:13:36 2014 geoffrey bauduin
// Last update Thu Mar  6 15:35:52 2014 geoffrey bauduin
//

#ifndef GAME_LEVEL_HPP_
# define GAME_LEVEL_HPP_

#define	LEVEL_1_DATA	"LEVEL1DATA"
#define	LEVEL_2_DATA	"LEVEL2DATA"
#define	LEVEL_3_DATA	"LEVEL3DATA"
#define	LEVEL_4_DATA	"LEVEL4DATA"
#define	LEVEL_5_DATA	"LEVEL5DATA"
#define	LEVEL_6_DATA	"LEVEL6DATA"
#define	LEVEL_7_DATA	"LEVEL7DATA"
#define	LEVEL_8_DATA	"LEVEL8DATA"
#define	LEVEL_9_DATA	"LEVEL9DATA"
#define	LEVEL_10_DATA	"LEVEL10DATA"

namespace	Game {

  namespace Level {

    struct Data {
      unsigned int	xp;
      Kernel::Serial	data;
    };

  }

}

#endif
