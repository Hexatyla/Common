//
// IClonable.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Mon Mar  3 22:17:34 2014 geoffrey bauduin
// Last update Mon Mar  3 22:18:26 2014 geoffrey bauduin
//

#ifndef ICLONABLE_HPP_
# define ICLONABLE_HPP_

template<class C>
class	IClonable {

public:
  virtual ~IClonable(void) {}

  C	*clone(void) const;
  void	clone(const C *) const;

};

#endif
