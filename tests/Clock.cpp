//
// Clock.cpp for  in /home/geoffrey/Projects/Hexatyla/Common
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Fri Apr  4 17:37:21 2014 geoffrey bauduin
// Last update Sun Apr  6 15:47:47 2014 geoffrey bauduin
//

#include	"Clock.hpp"
#include	"gtest/gtest.h"
#include	<stdlib.h>

TEST(Clock, testInitUpdate) {
  Clock clock;
  EXPECT_EQ(clock.getElapsedTime(), 0.0);
  clock.init();
  EXPECT_EQ(clock.getElapsedTime(), 0.0);
  usleep(500);
  clock.update();
  double old = clock.getElapsedTime();
  EXPECT_NE(old, 0.0);
  usleep(5000);
  clock.update();
  EXPECT_NE(clock.getElapsedTime(), old);
  EXPECT_GT(clock.getElapsedTime() - old, 0.0005);
}

TEST(Clock, testElapsedTimeLastCall) {
  Clock clock;
  clock.init();
  EXPECT_EQ(clock.getElapsedTimeSinceLastCall(), 0.0);
  usleep(500);
  double e = clock.getElapsedTimeSinceLastCall();
  EXPECT_NE(e, 0.0);
  EXPECT_GT(e, 0.0005);
}
