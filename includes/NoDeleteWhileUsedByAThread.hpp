//
// NoDeleteWhileUsedByAThread.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Tue Mar  4 18:26:05 2014 geoffrey bauduin
// Last update Wed Mar  5 11:22:28 2014 geoffrey bauduin
//

#ifndef NODELETEWHILEUSEDBYATHREAD_HPP_
# define NODELETEWHILEUSEDBYATHREAD_HPP_

#include	"Threading/Mutex.hpp"
#include	"IFromFactory.hpp"
#include	"Threading/CondVar.hpp"

class	NoDeleteWhileUsedByAThread: virtual public IFromFactory {

private:
  Mutex	*_mutex;
  bool	_deleting;
  CondVar	*_cond;
  int	_nbr;

public:
  NoDeleteWhileUsedByAThread(void);
  virtual ~NoDeleteWhileUsedByAThread(void);

  void	init(void);
  virtual void	destroy(void);

  bool	lock(void);
  void	lockDestroy(void);
  void	unlock(void);

};

#endif
