//
// ScopeLock.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Jan 21 09:58:41 2014 geoffrey bauduin
// Last update Tue Jan 21 10:00:16 2014 geoffrey bauduin
//

#ifndef SCOPELOCK_HPP_
# define SCOPELOCK_HPP_

#include	"Threading/Mutex.hpp"

class	ScopeLock {

private:
  Mutex	*_mutex;

public:
  ScopeLock(Mutex *);
  ~ScopeLock(void);

};

#endif
