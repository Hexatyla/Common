//
// MD5.cpp for  in /home/geoffrey/Projects/Hexatyla/Common
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Fri Apr  4 17:26:50 2014 geoffrey bauduin
// Last update Fri Apr  4 17:34:59 2014 geoffrey bauduin
//

#include	"Algo/MD5.hpp"
#include	"gtest/gtest.h"

TEST(AlgoMD5, testDigest1) {
  std::string f = "admin";
  std::string to = Algo::MD5::getInstance()->digest(f);
  EXPECT_EQ(to, "21232f297a57a5a743894a0e4a801fc3");
  EXPECT_NE(to, "21232f297a57a5a743894a0e4a801fc4");
}
