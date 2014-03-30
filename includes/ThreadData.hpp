//
// ThreadData.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Mon Feb 24 17:53:55 2014 geoffrey bauduin
// Last update Sun Mar 30 14:43:55 2014 geoffrey bauduin
//

#ifndef THREADDATA_HPP_
# define THREADDATA_HPP_

#include	"Clock.hpp"

enum	ThreadStatus {
  SLEEPING,
  WORKING
};

struct ThreadData {
  unsigned int	id;
  ThreadStatus	status;
  Clock		*clock;
  unsigned int	event;
};


#endif
