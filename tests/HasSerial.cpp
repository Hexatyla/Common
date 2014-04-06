//
// HasSerial.cpp for  in /home/geoffrey/Projects/Hexatyla/Common
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Sun Apr  6 16:00:06 2014 geoffrey bauduin
// Last update Sun Apr  6 16:01:11 2014 geoffrey bauduin
//

#include	"HasSerial.hpp"
#include	"gtest/gtest.h"

TEST(HasSerial, get) {
  HasSerial s;
  EXPECT_EQ(s.serial(), "");
  s.init("toto");
  EXPECT_EQ(s.serial(), "toto");
  s.destroy();
}
