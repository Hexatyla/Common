//
// Clock.hpp for  in /home/geoffrey/Projects/r-type
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Oct 25 13:38:07 2013 geoffrey bauduin
// Last update Mon Mar  3 22:18:43 2014 geoffrey bauduin
//

#ifndef SERVER_CLOCK_HPP_
# define SERVER_CLOCK_HPP_

#include	<stdexcept>
#include	<time.h>
#include  <sstream>
#include	"IFromFactory.hpp"
#include	"IClonable.hpp"

class	Clock: virtual public IFromFactory, public IClonable<Clock> {

public:
  enum Status {
    PLAY,
    PAUSE
  };

private:
  Status		_status;
  struct timeval	_startTime;
  struct timeval	_currentTime;
  struct timeval	_oldTime;
  struct timeval	_pauseTime;
  struct timeval	_playTime;
  struct timeval	_last;
  std::string   clock_s;

  double	timevalToDouble(const struct timeval &) const;
  void	getTime(struct timeval &);

public:
  Clock(void);
  ~Clock(void);

  bool	init(void);
  void	update(void);
  double	getElapsedTime(void) const;
  Clock	*clone(void) const;
  const std::string & getTimeToString(char);
  double	getElapsedTimeSince(const Clock *) const;
  double	getElapsedTimeSinceLastCall(void);
  void	clone(const Clock *);
  virtual void destroy(void);

  class	Exception: public std::exception {

  private:
    std::string	_what;

  public:
    Exception(const std::string &) throw();
    virtual ~Exception(void) throw();

    const char *what(void) const throw();

  };

};


struct timeval	operator+(const struct timeval &, const struct timeval &);
struct timeval	operator-(const struct timeval &, const struct timeval &);

#endif
