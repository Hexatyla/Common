//
// Date.cpp<2> for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sat Jan 18 16:08:50 2014 geoffrey bauduin
// Last update Fri Mar 21 14:17:10 2014 geoffrey bauduin
//

#include	<sys/time.h>
#include	<time.h>
#include	<sstream>
#include	<iomanip>
#include	"Date.hpp"

const std::string	Date::getTime(bool ms) {
  tm			*tm;
  struct timeval	t;
  std::stringstream	v;

  gettimeofday(&t, NULL);
  tm = localtime(&t.tv_sec);
  v << std::setw(2) << std::setfill('0') << tm->tm_hour << ":";
  v << std::setw(2) << std::setfill('0') << tm->tm_min << ":";
  v << std::setw(2) << std::setfill('0') << tm->tm_sec;
  if (ms) {
    v << "." << std::setw(6) << std::setfill('0') << t.tv_usec;
  }
  return (v.str());
}

const std::string	Date::getFilenameDateTime(void) {
  tm			*tm;
  struct timeval	t;
  char	buf[80];

  gettimeofday(&t, NULL);
  tm = localtime(&t.tv_sec);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%H-%M-%S", tm);
  return (buf);
}
