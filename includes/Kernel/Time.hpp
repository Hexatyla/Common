//
// Time.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sun Jan 12 14:27:33 2014 geoffrey bauduin
// Last update Wed Feb 12 17:25:16 2014 geoffrey bauduin
//

#ifndef KERNEL_TIME_HPP_
# define KERNEL_TIME_HPP_

#include	"IFromFactory.hpp"

namespace	Kernel {

  class	Time: public IFromFactory {

  public:
    enum	Canalisation {
      NONE,
      START,
      END,
      WHOLE
    };

    Canalisation	when;
    double		canalisation;
    double		creation;
    double		duration;
    double		cooldown;

  public:
    Time(void);
    virtual ~Time(void);

    void	init(double, double, double, double, Canalisation);
    virtual void	destroy(void);

  };

}

#endif
