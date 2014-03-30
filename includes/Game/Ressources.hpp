//
// Ressources.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sun Jan 12 13:58:43 2014 geoffrey bauduin
// Last update Mon Mar 17 14:29:28 2014 geoffrey bauduin
//

#ifndef GAME_RESSOURCES_HPP_
# define GAME_RESSOURCES_HPP_

#include	<iostream>
#include	<string>
#include	<map>
#include	"IFromFactory.hpp"
#include	"Threading/Mutex.hpp"

namespace	Game {

  class	Ressources: virtual public IFromFactory {

  public:
    enum	Type {
      GOLD,
      WOOD,
      FOOD
    };

  private:
    static const std::map<Type, std::string>	_hashtab;
    static const std::map<Type, std::string>	initHashtab(void);
    mutable Mutex			*_mutex;

  protected:
    std::map<Type, int>		_amount;

    void	_set(Game::Ressources::Type, int);

  public:
    static const std::string	&translate(Type);

    Ressources(void);
    Ressources(const Ressources &);
    virtual ~Ressources(void);

    Game::Ressources &operator=(const Game::Ressources &);

    void	init(unsigned int, unsigned int, unsigned int);
    virtual void destroy(void);

    void	set(Type, unsigned int);
    void	add(Type, int);
    int		get(Type) const;
    Game::Ressources &operator+=(const Game::Ressources &);
    Game::Ressources &operator-=(const Game::Ressources &);
    bool	hasEnough(const Game::Ressources &) const;

  };

}

#endif
