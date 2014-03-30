//
// Exception.cpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 10 15:51:22 2014 gautier lefebvre
// Last update Thu Jan 23 13:53:34 2014 gautier lefebvre
//

#include	"Network/Exception.hpp"

Network::Exception::Exception(const std::string &what) throw():
  _what(what)
{}

Network::Exception::~Exception() throw() {}

const char *Network::Exception::what() const throw() { return (this->_what.c_str()); }
