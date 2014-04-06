//
// Converter.cpp for  in /home/geoffrey/Projects/Hexatyla/Common
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Sun Apr  6 15:48:50 2014 geoffrey bauduin
// Last update Sun Apr  6 15:55:04 2014 geoffrey bauduin
//

#include	"Converter.hpp"
#include	"gtest/gtest.h"

TEST(Converter, stringOf) {
  std::string r = Converter::StringOf<int>(1);
  EXPECT_EQ("1", r);
}

TEST(Converter, stringTo) {
  int r = Converter::StringTo<int>("1");
  EXPECT_EQ(1, r);
}

TEST(Converter, convert) {
  int r = Converter::convert<std::string, int>("1");
  EXPECT_EQ(1, r);
}
