//
// Pool.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Jan 21 10:17:19 2014 geoffrey bauduin
// Last update Tue Jan 21 16:40:18 2014 geoffrey bauduin
//

#ifndef THREAD_POOL_HPP_
# define THREAD_POOL_HPP_

#include	<vector>
#include	"Singleton.hpp"
#include	"Threading/Thread.hpp"

#define DEFINE_FOR_ME	(static_cast<unsigned int>(-1))
#define THREADS_PER_CORE 3

class	ThreadPool {
  
private:
  std::vector<Thread *>	_th;
  unsigned int		_number;

public:
  ThreadPool(unsigned int);
  ~ThreadPool(void);

  bool	start(void *(*)(void *), void *);
  void	wait(void);
  unsigned int getNumberOfThreads(void) const;

};

#endif
