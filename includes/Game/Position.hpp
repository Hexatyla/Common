//
// Position.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 17:11:41 2014 geoffrey bauduin
// Last update Tue Feb 18 23:58:35 2014 geoffrey bauduin
//

#ifndef	GAME_POSITION_HPP_
# define GAME_POSITION_HPP_

#include	"Vector.hpp"
#include	"IFromFactory.hpp"

namespace	Game {

  class	Position: virtual public IFromFactory {

  protected:
    Vector3d	_position;
    int		_orientation;

  public:
    Position(void);
    virtual ~Position(void);

    void	init(int, double, double, double);
    virtual void	destroy(void);

    double	getX(void) const;
    double	getY(void) const;
    double	getZ(void) const;
    int		getOrientation(void) const;
    const Vector3d &getPosition(void) const;

  };

}

#endif
