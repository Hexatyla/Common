//
// CondVar.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Jan 21 09:47:27 2014 geoffrey bauduin
// Last update Tue Jan 21 10:03:38 2014 geoffrey bauduin
//

#ifndef CONDVAR_HPP_
# define CONDVAR_HPP_

#include	<pthread.h>
#include	"Threading/Mutex.hpp"

class	CondVar {

private:
  Mutex			_mutex;
  pthread_cond_t	_cond;

public:
  CondVar(void);
  ~CondVar(void);

  void	wait(void);
  bool	timewait(unsigned int);
  void	signal(void);
  void	broadcast(void);

};

#endif
