//
// main.cpp for  in /home/geoffrey/Projects/Hexatyla/Common/tests
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Fri Apr  4 17:05:42 2014 geoffrey bauduin
// Last update Fri Apr  4 17:25:46 2014 geoffrey bauduin
//

#include	"gtest/gtest.h"

int	main(int ac, char **av) {
  ::testing::InitGoogleTest(&ac, av);
  return (RUN_ALL_TESTS());
}
