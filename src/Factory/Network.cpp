//
// Network.cpp<2> for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 24 15:28:10 2014 gautier lefebvre
// Last update Sun Mar 30 14:47:20 2014 geoffrey bauduin
//

#include	"Factory/Pool.hpp"
#include	"Factory/Network.hpp"

static Pool< ::Network::SSocket>	*poolSocket = NULL;

void		Factory::Network::init() {
  poolSocket = new Pool< ::Network::SSocket>(100, 20, "Network::SSocket");
}

void		Factory::Network::end() {
  delete poolSocket;
}

::Network::SSocket *	Factory::Network::SSocket::create() {
  ::Network::SSocket *s = poolSocket->get();
  s->init();
  return (s);
}

void		Factory::Network::SSocket::remove(::Network::SSocket *s) {
  s->destroy();
  poolSocket->push(s);
}
