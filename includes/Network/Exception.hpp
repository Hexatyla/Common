//
// Exception.hpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 10 15:51:10 2014 gautier lefebvre
// Last update Thu Jan 23 13:52:54 2014 gautier lefebvre
//

#ifndef		__NETWORK_EXCEPTION_HPP__
#define		__NETWORK_EXCEPTION_HPP__

#include	<string>
#include	<exception>

namespace	Network {
  class		Exception :public std::exception {
  private:
    std::string	_what;

  public:
    Exception(const std::string &) throw();
    virtual ~Exception() throw();

    virtual const char *what() const throw();
  };
}

#endif
