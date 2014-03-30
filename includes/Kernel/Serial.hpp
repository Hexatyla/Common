//
// Serial.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Thu Jan 16 17:55:42 2014 geoffrey bauduin
// Last update Tue Mar 25 17:32:44 2014 geoffrey bauduin
//

#ifndef KERNEL_SERIAL_HPP_
# define KERNEL_SERIAL_HPP_

#include	<string>

namespace	Kernel {

  // class	Serial : public std::string {

  // public:
  //   Serial(void);
  //   Serial(const char *);
  //   virtual ~Serial(void);

  //   Serial	&operator=(const char *);

  // };
  typedef std::string Serial;

  const Serial	create_serial(const std::string &data);
  void	assign_serial(char *, const std::string &);
  const Kernel::Serial	get_serial(const char *);

}

#endif
