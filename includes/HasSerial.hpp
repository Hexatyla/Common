//
// HasSerial.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Jan 14 15:44:54 2014 geoffrey bauduin
// Last update Wed Feb 12 17:15:11 2014 geoffrey bauduin
//

#ifndef HASSERIAL_HPP_
# define HASSERIAL_HPP_

#include	<string>
#include	"Kernel/Serial.hpp"
#include	"IFromFactory.hpp"

class	HasSerial: virtual public IFromFactory {

protected:
  Kernel::Serial	_serial;

public:
  HasSerial(void);
  virtual ~HasSerial(void);

  void	init(const Kernel::Serial &);
  virtual void destroy(void);
  const Kernel::Serial	&serial(void) const;

};

#endif
