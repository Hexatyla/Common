//
// Clock.cpp for  in /home/geoffrey/Projects/r-type
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Oct 25 13:38:06 2013 geoffrey bauduin
// Last update Wed Feb 12 17:19:52 2014 geoffrey bauduin
//

#include	"Clock.hpp"
#include	<iostream>
#include	<sys/time.h>
#include	"Factory/Factory.hpp"

Clock::Clock(void):
  _status(Clock::PLAY),
  _startTime({0, 0}), _currentTime({0, 0}),
  _oldTime({0, 0}), _pauseTime({0, 0}), _playTime({0, 0}),
  _last({0, 0}) {

}

Clock::~Clock(void) {}

Clock	*Clock::clone(void) const {
  Clock	*clock = Factory::Clock::create();
  clock->_status = this->_status;
  clock->_startTime = this->_startTime;
  clock->_currentTime = this->_currentTime;
  clock->_oldTime = this->_oldTime;
  clock->_pauseTime = this->_pauseTime;
  clock->_playTime = this->_playTime;
  clock->_last = this->_last;
  return (clock);
}

void	Clock::clone(const Clock *c) {
  this->_status = c->_status;
  this->_startTime = c->_startTime;
  this->_currentTime = c->_currentTime;
  this->_oldTime = c->_oldTime;
  this->_pauseTime = c->_pauseTime;
  this->_playTime = c->_playTime;
  this->_last = c->_last;
}

bool	Clock::init(void) {
  this->getTime(this->_startTime);
  this->_currentTime = this->_startTime;
  this->_last = this->_startTime;
  return (true);
}

void	Clock::destroy(void) {

}

void	Clock::getTime(struct timeval &t) {
  if (gettimeofday(&t, NULL) == -1) {
    throw new Clock::Exception("Cannot update clock");
  }
}

void	Clock::update(void) {
  this->_oldTime = this->_currentTime;
  this->getTime(this->_currentTime);
  switch (this->_status) {
    
  case Clock::PAUSE:
    this->_pauseTime = this->_pauseTime + (this->_currentTime - this->_oldTime);
    break;
 
  case Clock::PLAY:
    this->_playTime = this->_playTime + (this->_currentTime - this->_oldTime);
    break;

  }
}

double	Clock::timevalToDouble(const struct timeval &t) const {
  double	eTime;
  eTime = static_cast<double>(t.tv_sec);
  eTime += static_cast<double>(t.tv_usec) / 1000000.0;
  return (eTime);
}

double	Clock::getElapsedTime(void) const {
  return (this->timevalToDouble(this->_playTime));
}

double	Clock::getElapsedTimeSince(const Clock *rhs) const {
  struct timeval	t;

  t = this->_playTime - rhs->_playTime;
  return (this->timevalToDouble(t));
}

double	Clock::getElapsedTimeSinceLastCall(void) {
  struct timeval t;
  this->getTime(t);
  struct timeval diff = t - this->_last;
  this->_last = t;
  return (this->timevalToDouble(diff));
}

const std::string &Clock::getTimeToString(char v)
{
  this->update();
  double value = this->getElapsedTime();
  unsigned int hours  = value / 3600;
  unsigned int min    = (value - (hours * 3600)) / 60;
  unsigned int sec    = (value - (hours * 3600) - (min * 60));
  std::ostringstream oss;
  if (v == 1)
  {
    if (min < 10)
      oss << "0";
    oss << min;
    oss << ":";
    if (sec < 10)
      oss << "0";
    oss << sec;
    clock_s = oss.str();
  }
  else
  {
    oss << hours;
    oss << ":";
    if (min < 10)
      oss << "0";
    oss << min;
    oss << ":";
    if (sec < 10)
      oss << "0";
    oss << sec;
    clock_s = oss.str();
  }
  return (clock_s);
}

struct timeval	operator+(const struct timeval &t1, const struct timeval &t2) {
  struct timeval	res;

  res.tv_usec = t1.tv_usec + t2.tv_usec;
  res.tv_sec = res.tv_usec / 1000000;
  res.tv_usec %= 1000000;
  res.tv_sec += t1.tv_sec + t2.tv_sec;
  return (res);
}

struct timeval	operator-(const struct timeval &t1, const struct timeval &t2) {
  struct timeval	res;

  res.tv_usec = t1.tv_usec - t2.tv_usec;
  res.tv_sec = t1.tv_sec - t2.tv_sec;
  while (res.tv_usec < 0)
    {
      res.tv_usec += 1000000;
      res.tv_sec--;
    }
  return (res);
}

Clock::Exception::Exception(const std::string &what) throw():
  _what(what) {}

Clock::Exception::~Exception(void) throw() {}

const char	*Clock::Exception::what(void) const throw() {
  return (this->_what.c_str());
}
