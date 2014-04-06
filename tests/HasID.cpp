//
// HasID.cpp for  in /home/geoffrey/Projects/Hexatyla/Common
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Sun Apr  6 15:56:12 2014 geoffrey bauduin
// Last update Sun Apr  6 15:57:06 2014 geoffrey bauduin
//

#include	"HasID.hpp"
#include	"gtest/gtest.h"

TEST(HasID, getID) {
  HasID id;
  id.init(10);
  EXPECT_EQ(id.getID(), 10);
  id.destroy();
}
