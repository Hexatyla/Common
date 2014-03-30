//
// Movable.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 17:15:00 2014 geoffrey bauduin
// Last update Thu Mar 13 17:35:31 2014 geoffrey bauduin
//

#ifndef GAME_MOVABLE_HPP_
# define GAME_MOVABLE_HPP_

#include	<deque>
#include	<vector>
#include	"Game/Position.hpp"
#include	"IFromFactory.hpp"
#include	"Threading/Mutex.hpp"
#include	"Vector.hpp"

namespace	Game {

  class	Movable: virtual public Game::Position, virtual public IFromFactory {

  private:
    mutable Mutex		*_mutex;

  protected:
    std::deque<Vector3d>	_waypoints;

    void			clearWaypoints(void);

  public:
    Movable(void);
    virtual ~Movable(void);

    virtual void	init(int, double, double, double);
    virtual void	destroy(void);

    virtual void	setX(double);
    virtual void	setY(double);
    virtual void	setZ(double);
    virtual void	setPosition(double, double, double);
    virtual void	setOrientation(int);

    virtual void	setWaypoints(const std::vector<Vector3d> &);

    const std::deque<Vector3d>	&getWaypoints(void) const;
    bool		hasWaypoints(void) const;
    const Vector3d	&getFrontWaypoint(void) const;
    void		popWaypoints(void);

  };

}

#endif
