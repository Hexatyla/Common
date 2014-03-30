//
// Date.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sat Jan 18 16:08:11 2014 geoffrey bauduin
// Last update Fri Mar 21 14:10:20 2014 geoffrey bauduin
//

#ifndef DATE_HPP_
# define DATE_HPP_

#include	<string>

class	Date {

public:
  static const std::string	getTime(bool ms = false);
  static const std::string	getFilenameDateTime(void);

};

#endif
