//
// Protocol.cpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Tue Jan 21 15:02:43 2014 gautier lefebvre
// Last update Thu Mar 13 17:12:25 2014 geoffrey bauduin
//

#include	"Factory/Protocol.hpp"
#include	"Factory/Pool.hpp"

static Pool< ::Protocol::Job>	*poolJob = NULL;

void		Factory::Protocol::init() {
  poolJob = new Pool< ::Protocol::Job>(2500, 750, "Protocol::Job");
}

void		Factory::Protocol::end() {
  delete (poolJob);
}

::Protocol::Job*	Factory::Protocol::Job::create() {
  ::Protocol::Job* j = poolJob->get();
  //::Protocol::Job *j = new ::Protocol::Job;
  j->reset();
  return (j);
}

void		Factory::Protocol::Job::remove(::Protocol::Job* j) {
  if (j) {
    // delete j;
    // return ;
    poolJob->push(j);
  }
}
