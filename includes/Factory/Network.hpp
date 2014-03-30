//
// Network.cpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 24 15:25:56 2014 gautier lefebvre
// Last update Sun Mar 30 14:47:24 2014 geoffrey bauduin
//

#ifndef		__FACTORY_NETWORK_HPP__
#define		__FACTORY_NETWORK_HPP__

#include	"Network/Socket.hpp"

namespace	Factory {
  namespace	Network {
    void	init();
    void	end();

    class	SSocket {
    public:
      static ::Network::SSocket *create();
      static void		remove(::Network::SSocket *);
    };
  }
}

#endif
