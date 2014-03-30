//
// Map.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 24 16:44:31 2014 geoffrey bauduin
// Last update Wed Mar 26 11:37:06 2014 geoffrey bauduin
//

#ifndef GAME_MAP_HPP_
# define GAME_MAP_HPP_

#include	<map>
#include	<vector>
#include	<list>
#include	"Vector.hpp"
#include	"Game/Team.hpp"
#include	"Game/AElement.hpp"
#include	"Direction.hpp"
#include	"IFromFactory.hpp"
#include	"Threading/Mutex.hpp"

namespace	Game {

  class	Map: virtual public IFromFactory {

  public:
    class	Node: public Vector3d, virtual public IFromFactory {
    public:
      int xi;
      int yi;
      std::map<const Game::Team *, int>	visible;
      std::map<Direction, Node *> neighbors;
      std::list<const ::Game::AElement *> range;

      Node(void);
      Node(double, double, double);
      virtual ~Node(void);
      void init(void);
      virtual void destroy(void);

    };

    class	QuadTree: virtual public IFromFactory {
    private:
      enum where {
	NW,
	NE,
	SE,
	SW
      };
      mutable Mutex	*_mutex;
      Vector2d	_leftRight;
      Vector2d	_size;
      std::vector<QuadTree *>	_sons;
      std::list<const ::Game::AElement *> _elements;


      void	createSE(void);
      void	createSW(void);
      void	createNE(void);
      void	createNW(void);

      bool	containsCircle(double, double) const;
      bool	containsWholeCircle(double, double, double) const;
      bool	tryToPush(const ::Game::AElement *);
      bool	interCircleCircle(double, double, double, double, double, double) const;

      const std::vector<const ::Game::AElement *> *_objectsInRange(double, double, double);

    public:
      QuadTree(void);
      ~QuadTree(void);

      void	init(double, double, double, double);
      virtual void destroy(void);

      bool	push(const ::Game::AElement *);
      bool	remove(const ::Game::AElement *);
      bool	tryPosition(const ::Game::AElement *, double, double);
      const std::vector<const ::Game::AElement *> *objectsInRange(double, double, double);

    };


    unsigned int x;
    unsigned int y;
    unsigned int precision;

  private:
    void	movedItemRangeAndVision(const ::Game::AElement *, double, double);
    void	addItemRangeAndVision(const ::Game::AElement *, double, double, double, double);
    void	removeItemRangeAndVision(const ::Game::AElement *, double, double, double, double);

    bool	_isWalkable(double, double, double &) const;

    Game::Map::Node	*getNeighbor(Game::Map::Node *, unsigned int, unsigned int);

  protected:
    const std::vector<const ::Game::AElement *> *_objectsInRange(double, double, double);

  protected:
    std::vector<Node *>	_points;
    std::map<unsigned int, std::map<unsigned int, Vector3d> > _hexas;
    QuadTree		*_tree;
    bool		_day;
    mutable Mutex		*_mutex;
  public:
    const double	_hexaX;
    const double	_hexaY;

  protected:

    bool	isInSight(const ::Game::AElement *, const Game::Map::Node *, bool) const;
    bool	isInRange(const ::Game::AElement *, const Game::Map::Node *) const;
    void	getRange(const ::Game::AElement *, double, double &, double &, double &, double &) const;
    Game::Map::Node	*getNode(double, double) const;

    virtual bool	_push(const ::Game::AElement *, bool rv = true);
    virtual bool	_remove(const ::Game::AElement *, bool rv = true);

    virtual bool	_tryPosition(const ::Game::AElement *, double, double) const;

  public:
    Map(void);
    ~Map(void);

    void	init(unsigned int, unsigned int, const std::vector<unsigned int> &);
    virtual void	destroy(void);
    const std::map<unsigned int, std::map<unsigned int, Vector3d> > &getHexas(void) const;

    const std::vector<Node *> &getPoints(void) const;
    virtual bool	push(const ::Game::AElement *);
    virtual bool	remove(const ::Game::AElement *);
    bool	tryPosition(const ::Game::AElement *, double, double) const;

    unsigned int	getHeight(unsigned int, unsigned int) const;
    unsigned int	getHeightAt(double, double) const;

    bool	move(::Game::AElement *, ::Game::Movable *, double, double, double);

    bool	hasVision(const ::Game::Team *, double, double, double) const;

    const std::vector<const ::Game::AElement *> *objectsInRange(double, double, double);
    void	setDayNight(bool);

    virtual void	refreshUnitVisionAndRange(const ::Game::AElement *);

    const Vector3d &getHexa(unsigned int, unsigned int) const;

    bool	isVisible(const Game::Player *, const Game::AElement *) const;
    bool	hexaVisible(const Game::Team *, unsigned int, unsigned int) const;

  };

}

#endif
