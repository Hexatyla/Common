//
// IFromFactory.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Wed Feb 12 17:07:32 2014 geoffrey bauduin
// Last update Wed Feb 12 17:08:10 2014 geoffrey bauduin
//

#ifndef IFROMFACTORY_HPP_
# define IFROMFACTORY_HPP_

class	IFromFactory {

public:
  virtual ~IFromFactory(void) {}

  virtual void	destroy(void) = 0;

};

#endif
