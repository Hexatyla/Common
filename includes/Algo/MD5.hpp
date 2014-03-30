//
// MD5.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Thu Jan 16 15:45:36 2014 geoffrey bauduin
// Last update Wed Feb 26 14:19:58 2014 geoffrey bauduin
//

#ifndef ALGO_MD5_HPP_
# define ALGO_MD5_HPP_

#include	<string>
#include	"Singleton.hpp"

namespace	Algo {

  class	MD5: public Singleton<Algo::MD5> {

    friend class Singleton;

  private:
    MD5(void);
    virtual ~MD5(void);

  public:
    const std::string	digest(const std::string &);

  };

}

#endif
