//
// Protocol.hpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Tue Jan 21 15:00:41 2014 gautier lefebvre
// Last update Tue Jan 21 15:02:26 2014 gautier lefebvre
//

#ifndef		__FACTORY_PROTOCOL_HPP__
#define		__FACTORY_PROTOCOL_HPP__

#include	"Protocol/Job.hpp"

namespace	Factory {
  namespace	Protocol {
    void	init();
    void	end();

    class	Job {
    public:
      static ::Protocol::Job*	create();
      static void		remove(::Protocol::Job*);
    };
  }
}

#endif
