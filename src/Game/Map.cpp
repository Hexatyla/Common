//
// Map.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 24 16:47:39 2014 geoffrey bauduin
// Last update Wed Mar 26 16:47:00 2014 geoffrey bauduin
//

#define BETWEEN(a, x, b)	((a) <= (x) && (x) < (b))
#define DOUBLE(x)		(static_cast<double>(x))
#define SQUARE(x)		((x) * (x))
#define	OFFSET(i, j)		((j) * lineSize + (i))
#include	<cstddef>
#include	<assert.h>
#include	<math.h>
#include	<algorithm>
#include	"Game/Map.hpp"
#include	"Factory/Game.hpp"
#include	"Threading/ScopeLock.hpp"
#include	"Utils/Hexagon.hpp"
#include	"Logger.hpp"
#include	"Kernel/Config.hpp"

#define DEBUG_LOL
#define DEBUG_LOLZ	{ std::string ffff = __PRETTY_FUNCTION__; int llllll = __LINE__; Logger::getInstance()->logf("LOCK MUTEX %s %d", Logger::DEBUG, &ffff, llllll); }

Game::Map::Node::Node(void):
  Vector3d(), visible(), neighbors() {
}

Game::Map::Node::Node(double x, double y, double z):
  Vector3d(x, y, z), visible() {

}

Game::Map::Node::~Node(void) {}

void	Game::Map::Node::init(void) {
  this->x = 0.0;
  this->y = 0.0;
  this->z = 0.0;
}

void	Game::Map::Node::destroy(void) {
  this->visible.clear();
  this->neighbors.clear();
}

Game::Map::QuadTree::QuadTree(void):
  _mutex(new Mutex), _leftRight(), _size(), _sons(4, NULL), _elements() {

}

Game::Map::QuadTree::~QuadTree(void) {
  delete this->_mutex;
}

void	Game::Map::QuadTree::createNE(void) {
  this->_sons[NE] = Factory::Game::Map::QuadTree::create(this->_leftRight.x + this->_size.x / 2.0,
							 this->_leftRight.y,
							 this->_size.x / 2.0,
							 this->_size.y / 2.0);
}

void	Game::Map::QuadTree::createNW(void) {
  this->_sons[NW] = Factory::Game::Map::QuadTree::create(this->_leftRight.x,
							 this->_leftRight.y,
							 this->_size.x / 2.0,
							 this->_size.y / 2.0);
}

void	Game::Map::QuadTree::createSW(void) {
  this->_sons[SW] = Factory::Game::Map::QuadTree::create(this->_leftRight.x,
							 this->_leftRight.y + this->_size.y / 2.0,
							 this->_size.x / 2.0,
							 this->_size.y / 2.0);
}

void	Game::Map::QuadTree::createSE(void) {
  this->_sons[SE] = Factory::Game::Map::QuadTree::create(this->_leftRight.x + this->_size.x / 2.0,
							 this->_leftRight.y + this->_size.y / 2.0,
							 this->_size.x / 2.0,
							 this->_size.y / 2.0);
}

void	Game::Map::QuadTree::init(double x, double y, double width, double height) {
  this->_leftRight = Vector2d(x, y);
  this->_size = Vector2d(width, height);
}

void	Game::Map::QuadTree::destroy(void) {
  this->_elements.clear();
  for (unsigned int i = 0 ; i < this->_sons.size() ; ++i) {
    if (this->_sons[i]) {
      Factory::Game::Map::QuadTree::remove(this->_sons[i]);
      this->_sons[i] = NULL;
    }
  }
}

struct pointsRepartition {
  int multX1;
  int multY1;
  int multX2;
  int multY2;
};

static const pointsRepartition points_table[4] = {
  {0, 0, 1, 0},
  {0, 0, 0, 1},
  {0, 1, 1, 1},
  {1, 0, 1, 1}
};

bool	Game::Map::QuadTree::containsWholeCircle(double xc, double yc, double r) const {
  // Check if the middle of the circle is in the square
  if (BETWEEN(this->_leftRight.x, xc, this->_leftRight.x + this->_size.x) &&
      BETWEEN(this->_leftRight.y, yc, this->_leftRight.y + this->_size.y)) {
    // Check if the square intersects the circle
    /*
    ** Equation : ((1−t)⋅x1+t⋅x2−xC)^2+((1−t)⋅y1+t⋅y2−yC)^2=r^2 
    **           <=> At^2 + Bt + C = 0
    **         avec A = (x1 - x2)^2 + (y1 - y2)^2
    **              B = 2 * ((x2 - x1)(x1 - xc) + (y2 - y1)(y1 - yc))
    **              C = (x1 - xc)^2 + (y1 - yc)^2 - R^2
    */
    double x1, x2, y1, y2, a, b, c, delta;
    for (int i = 0 ; i < 4 ; ++i) {
      x1 = this->_leftRight.x + points_table[i].multX1 * this->_size.x;
      y1 = this->_leftRight.y + points_table[i].multY1 * this->_size.y;
      x2 = this->_leftRight.x + points_table[i].multX2 * this->_size.x;
      y2 = this->_leftRight.y + points_table[i].multY2 * this->_size.y;
      a = SQUARE(x1 - x2) + SQUARE(y1 - y2);
      b = 2.0 * ((x2 - x1) * (x1 - xc) + (y2 - y1) * (y1 - yc));
      c = SQUARE(x1 - xc) + SQUARE(y1 - yc) - SQUARE(r);
      delta = SQUARE(b) - 4.0 * a * c;
      if (delta >= 0) {
	return (false);
      }
    }
    return (true);
  }
  return (false);
}

bool	Game::Map::QuadTree::tryToPush(const ::Game::AElement *element) {
  return (false);
  //  Logger::getInstance()->log("TRY TO PUSH LOL");
  if (!this->_sons[NW]) {
    this->createNW();
  }
  //    Logger::getInstance()->log("PUSH IN NW ??");
  assert(this->_sons[NW] != this);
  if (this->_sons[NW]->push(element)) {
    return (true);
  }
  if (!this->_sons[NE]) {
    this->createNE();
  }
  Logger::getInstance()->log("PUSH IN NE ??");
  assert(this->_sons[NE] != this);
  if (this->_sons[NE]->push(element)) {
    return (true);
  }
  if (!this->_sons[SE]) {
    this->createSE();
  }
  Logger::getInstance()->log("PUSH IN SE ??");
  assert(this->_sons[SE] != this);
  if (this->_sons[SE]->push(element)) {
    return (true);
  }
  if (!this->_sons[SW]) {
    this->createSW();
  }
  Logger::getInstance()->log("PUSH IN SW ??");
  assert(this->_sons[SW] != this);
  if (this->_sons[SW]->push(element)) {
      return (true);
  }
  return (false);
}

bool	Game::Map::QuadTree::push(const ::Game::AElement *element) {
  DEBUG_LOL
  ScopeLock s(this->_mutex);
  DEBUG_LOL
  if (this->containsWholeCircle(element->getX(), element->getY(), element->getHitbox())) {
    for (auto it : this->_sons) {
      if (it && it->push(element)) {
	return (true);
      }
    }
    if (!this->tryToPush(element)) {
      this->_elements.push_back(element);
    }
    return (true);
  }
  return (false);
}

bool	Game::Map::QuadTree::remove(const ::Game::AElement *element) {
  ScopeLock s(this->_mutex);
  if (this->containsWholeCircle(element->getX(), element->getY(), element->getHitbox())) {
    for (auto it : this->_sons) {
      if (it && it->remove(element)) {
	return (true);
      }
    }
    this->_elements.remove(element);
    return (true);
  }
  return (false);
}

bool Game::Map::QuadTree::interCircleCircle(double x1, double y1, double r1, double x2, double y2, double r2) const {
  /* http://math.15873.pagesperso-orange.fr/IntCercl.html */
  double q = (x1 - x2) / (y1 - y2);
  double n = SQUARE(r2) - (SQUARE(r1) - SQUARE(x2) + SQUARE(x1) - SQUARE(y2) + SQUARE(y1)) / (2.0 * (y2 - y1));
  double a = SQUARE(q) + 1;
  double b = 2.0 * (y1 * q - n * q - x1);
  double c = SQUARE(x1) + SQUARE(y1) + SQUARE(n) - SQUARE(r1) - 2.0 * y1 * n;
  double delta = SQUARE(b) - 4.0 * a * c;
  return (delta > 0);
}

bool	Game::Map::QuadTree::containsCircle(double x, double y) const {
  return (BETWEEN(this->_leftRight.x, x, this->_leftRight.x + this->_size.x) &&
	  BETWEEN(this->_leftRight.y, y, this->_leftRight.y + this->_size.y));
}

bool	Game::Map::QuadTree::tryPosition(const ::Game::AElement *element, double x, double y) {
#ifndef __SERVER__
  return (true);
#endif
  ScopeLock s(this->_mutex);
  if (this->containsCircle(element->getX(), element->getY())) {
    for (auto it : this->_elements) {
      if (this->interCircleCircle(it->getX(), it->getY(), it->getInfos().data->hitbox,
				  x, y, element->getHitbox())) {
	if (!element->canPassThrough(it)) {
	  return (false);
	}
      }
    }
    for (auto it : this->_sons) {
      if (it && it->containsCircle(element->getX(), element->getY()) && !it->tryPosition(element, x, y)) {
	return (false);
      }
    }
    return (true);
  }
  return (false);
}

const std::vector<const ::Game::AElement *> *Game::Map::QuadTree::objectsInRange(double x, double y, double r) {
  ScopeLock s(this->_mutex);
  return (this->_objectsInRange(x, y, r));
}

const std::vector<const ::Game::AElement *> *Game::Map::QuadTree::_objectsInRange(double x, double y, double r) {
  std::vector<const ::Game::AElement *> *list = NULL;
  if (this->containsCircle(x, y)) {
    for (auto it : this->_elements) {
      if (this->interCircleCircle(it->getX(), it->getY(), it->getInfos().data->hitbox, x, y, r)) {
	if (!list) {
	  list = new std::vector<const ::Game::AElement *>;
	}
	list->push_back(it);
      }
    }
    for (auto it : this->_sons) {
      if (it) {
	const std::vector<const ::Game::AElement *> *nlist = it->objectsInRange(x, y, r);
	if (nlist) {
	  if (!list) {
	    list = new std::vector<const ::Game::AElement *>;
	  }
	  list->insert(list->end(), nlist->begin(), nlist->end());
	  delete nlist;
	}
      }
    }
  }
  return (list);
}

Game::Map::Map(void):
  x(0), y(0), precision(Kernel::Config::getInstance()->getUInt(Kernel::Config::MAP_PRECISION)), _points(), _hexas(), _tree(NULL), _mutex(new Mutex),
  _hexaX(0.5), _hexaY(sqrt(3.0) / 4.0) {

}

Game::Map::~Map(void) {
  delete this->_mutex;
}

void	Game::Map::destroy(void) {
  for (auto it : this->_points) {
    if (it) {
      Factory::Game::Map::Node::remove(it);
    }
  }
  this->_hexas.clear();
  this->_points.assign(0, NULL);
  Factory::Game::Map::QuadTree::remove(this->_tree);
  this->_tree = NULL;
}

void	Game::Map::init(unsigned int xm, unsigned int ym, const std::vector<unsigned int> &z) {
  this->x = xm;
  this->y = ym;
  this->_day = true;
  unsigned int totalSize = this->x * this->y * this->precision * this->precision;
  this->_points.assign(totalSize, NULL);
  double hx = 2.0 * this->_hexaX;
  double hy = 2.0 * this->_hexaY;
  for (unsigned int yu = 0 ; yu < this->y ; ++yu) {
    for (unsigned int xu = 0 ; xu < this->x ; ++xu) {
      this->_hexas[yu][xu] = Vector3d(3.0 * static_cast<double>(xu) * hx / 4.0,
				      (xu % 2 == 1 ? this->_hexaY : 0.0) + hy * static_cast<double>(yu),
				      z[yu * this->x + xu]);
    }
  }
  unsigned int idx = 0;
  double z_;
  for (unsigned int yu = 0 ; yu < this->y * this->precision ; ++yu) {
    for (unsigned int xu = 0 ; xu < this->x * this->precision ; ++xu) {
      double x_ = DOUBLE(xu) * 1.0 / DOUBLE(this->precision);
      double y_ = DOUBLE(yu) * 1.0 / DOUBLE(this->precision);
      if (this->_isWalkable(x_, y_, z_)) {
	this->_points[idx] = Factory::Game::Map::Node::create();
	this->_points[idx]->x = x_;
	this->_points[idx]->xi = xu;
	this->_points[idx]->yi = yu;
	this->_points[idx]->y = y_;
	this->_points[idx]->z = z_;
      }
      else {
	this->_points[idx] = NULL;
      }
      idx++;
    }
  }
  unsigned int lineSize = this->x * this->precision;
  unsigned int nbrLines = this->y * this->precision;
  for (unsigned int j = 0 ; j < nbrLines ; ++j) {
    for (unsigned int i = 0 ; i < lineSize ; ++i) {
      ::Game::Map::Node *node = this->_points[OFFSET(i, j)];
      if (node) {
	node->neighbors[NORTH] = j == 0 ? NULL : this->getNeighbor(node, i, j - 1);//this->_points[OFFSET(i, j - 1)];
	node->neighbors[EAST] = i + 1 < lineSize ? this->getNeighbor(node, i + 1, j) : NULL;
	node->neighbors[SOUTH] = j + 1 < nbrLines ? this->getNeighbor(node, i, j + 1) : NULL;
	node->neighbors[WEST] = i == 0 ? NULL : this->getNeighbor(node, i - 1, j);
	node->neighbors[NORTH_EAST] = i + 1 < lineSize && j != 0 ? this->getNeighbor(node, i + 1, j - 1) : NULL;
	node->neighbors[SOUTH_EAST] = i + 1 < lineSize && j + 1 < nbrLines ? this->getNeighbor(node, i + 1, j + 1) : NULL;
	node->neighbors[SOUTH_WEST] = i != 0 && j + 1 < nbrLines ? this->getNeighbor(node, i - 1, j + 1) : NULL;
	node->neighbors[NORTH_WEST] = i != 0 && j != 0 ? this->getNeighbor(node, i - 1, j - 1) : NULL;
      }
    }
  }
  this->_tree = Factory::Game::Map::QuadTree::create(0.0, 0.0, DOUBLE(xm), DOUBLE(ym));
}

Game::Map::Node	*Game::Map::getNeighbor(Game::Map::Node *from, unsigned int x, unsigned int y) {
  Game::Map::Node *to = this->getNode(x, y);
  if (!to) {
    return (NULL);
  }
  if (SQUARE(from->z - to->z) <= 1) {
    return (to);
  }
  return (NULL);
}

bool	Game::Map::_isWalkable(double x, double y, double &z) const {
  double xi, xmax, yi, ymax;
  double step = (1.0 / DOUBLE(this->precision)) / 10.0;
  xmax = x + 1.0 / DOUBLE(this->precision);
  ymax = y + 1.0 / DOUBLE(this->precision);
  std::vector<Vector3d> hexas;
  Vector2d left, right;
  left.x = x - 2.0;
  left.y = y - 2.0;
  right.x = xmax + 2.0;
  right.y = ymax + 2.0;
  for (auto it : this->_hexas) {
    for (auto it2 : it.second) {
      if (left.x <= it2.second.x && it2.second.x <= right.x &&
	  left.y <= it2.second.y && it2.second.y <= right.y &&
	  it2.second.z > 0) {
	hexas.push_back(it2.second);
      }
    }
  }
  for (auto it : hexas) {
    for (xi = x ; xi < xmax ; xi += step) {
      for (yi = y ; yi < ymax ; yi += step) {
	if (Utils::inHexagon(2.0 * this->_hexaX, 2.0 * this->_hexaY,
			     0, true, xi - it.x, yi - it.y)) {
	  z = it.z;
	  return (true);
	}
      }
    }
  }
  return (false);
}

const std::vector<Game::Map::Node *>	&Game::Map::getPoints(void) const {
  return (this->_points);
}

bool	Game::Map::isInSight(const ::Game::AElement *element, const Game::Map::Node *node, bool day) const {
  double vx, vy, hb;
  vx = element->getX() - node->x;
  vy = element->getY() - node->y;
  if (day) {
    hb = element->getDaySight();
  }
  else {
    hb = element->getNightSight();
  }
  return (vx * vx + vy * vy <= hb * hb);
}

bool	Game::Map::isInRange(const ::Game::AElement *element, const Game::Map::Node *node) const {
  double vx, vy, vz, hb;
  vx = element->getX() - node->x;
  vy = element->getY() - node->y;
  vz = 0;//element->getZ() - node->z;
  hb = element->getAttackRange();
  return (vx * vx + vy * vy + vz * vz <= hb * hb);
}

bool	Game::Map::_push(const ::Game::AElement *element, bool rv) {
  if (this->_tree->push(element)) {
    if (rv) {
      double hb = std::max(element->getAttackRange(),
			   this->_day ? element->getDaySight() : element->getNightSight());
      this->addItemRangeAndVision(element,
				  element->getX() - hb - 1.0, element->getY() - hb - 1.0,
				  element->getX() + hb + 1.0 , element->getY() + hb + 1.0);
    }
    return (true);
  }
  return (false);
}

bool	Game::Map::push(const ::Game::AElement *element) {
  ScopeLock s(this->_mutex);
  return (this->_push(element));
}

bool	Game::Map::_remove(const ::Game::AElement *element, bool rv) {
  if (this->_tree->remove(element)) {
    if (rv) {
      double hb = std::max(element->getAttackRange(),
			   this->_day ? element->getDaySight() : element->getNightSight());
      this->removeItemRangeAndVision(element,
				     element->getX() - hb - 1.0, element->getY() - hb - 1.0,
				     element->getX() + hb + 1.0, element->getY() + hb + 1.0);
    }
    return (true);
  }
  return (false);
}

void	Game::Map::removeItemRangeAndVision(const ::Game::AElement * element,
					    double x1, double y1, double x2, double y2) {
  double step = 1.0 / static_cast<double>(this->precision);
  ::Game::Map::Node *node;
  for (double x = x1 ; x <= x2 ; x += step) {
    for (double y = y1 ; y <= y2 ; y += step) {
      node = this->getNode(x, y);
      if (node) {
	if (this->isInSight(element, node, this->_day)) {
	  node->visible[element->getTeam()]--;
	}
	if (this->isInRange(element, node)) {
	  node->range.remove(element);
	}
      }
    }
  }
}

void	Game::Map::addItemRangeAndVision(const ::Game::AElement *element,
					 double x1, double y1, double x2, double y2) {
  double step = 1.0 / static_cast<double>(this->precision);
  ::Game::Map::Node *node;
  for (double x = x1 ; x <= x2 ; x += step) {
    for (double y = y1 ; y <= y2 ; y += step) {
      node = this->getNode(x, y);
      if (node) {
	if (this->isInSight(element, node, this->_day)) {
	  node->visible[element->getTeam()]++;
	}
	if (this->isInRange(element, node)) {
	  node->range.push_back(element);
	}
      }
    }
  }
}

void	Game::Map::movedItemRangeAndVision(const ::Game::AElement *element, double x, double y) {
  double hb = std::max(element->getAttackRange(),
		       this->_day ? element->getDaySight() : element->getNightSight());
  this->removeItemRangeAndVision(element,
				 std::min(element->getX() - hb, x - hb), std::min(element->getY() - hb, y - hb),
				 std::max(element->getX() - hb, x - hb), std::max(element->getY() - hb, y - hb));
  this->addItemRangeAndVision(element,
			      std::min(element->getX() + hb, x + hb), std::min(element->getY() + hb, y + hb),
			      std::max(element->getX() + hb, x + hb), std::max(element->getY() + hb, y + hb));
}

bool	Game::Map::remove(const ::Game::AElement *element) {
  ScopeLock s(this->_mutex);
  return (this->_remove(element));
}

bool	Game::Map::tryPosition(const ::Game::AElement *element, double x, double y) const {
  ScopeLock s(this->_mutex);
  return (this->_tryPosition(element, x, y));
}

bool	Game::Map::_tryPosition(const ::Game::AElement *element, double x, double y) const {
  // Node *node = this->getNode(x, y);
  // if (!node || node->z == 0.0) {
  //   return (false);
  // }
  return (this->_tree->tryPosition(element, x, y));
}

const std::vector<const ::Game::AElement *> *Game::Map::objectsInRange(double x, double y, double r) {
  ScopeLock s(this->_mutex);
  return (this->_objectsInRange(x, y, r));
}

const std::vector<const ::Game::AElement *> *Game::Map::_objectsInRange(double x, double y, double r) {
  return (this->_tree->objectsInRange(x, y, r));
}

void	Game::Map::getRange(const ::Game::AElement *element, double box, double &x1, double &y1, double &x2, double &y2) const {
  x1 = element->getX() - box;
  y1 = element->getY() - box;
  x2 = element->getX() + box;
  y2 = element->getY() + box;
}

Game::Map::Node	*Game::Map::getNode(double x, double y) const {
  unsigned int yi = static_cast<unsigned int>(y * static_cast<double>(this->precision));
  unsigned int xi = static_cast<unsigned int>(x * static_cast<double>(this->precision));
  unsigned int lineSize = this->x * this->precision;
  if (OFFSET(xi, yi) < this->_points.size()) {
    Node *node = this->_points.at(OFFSET(xi, yi));
    return (node);
  }
  return (NULL);
}

void	Game::Map::setDayNight(bool day) {
  ScopeLock s(this->_mutex);
  if (this->_day == day) {
    return ;
  }
  this->_day = day;
  const std::vector<const Game::AElement *> *objects = this->_tree->objectsInRange(0.0, 0.0, this->x + this->y);
  if (!objects) {
    return ;
  }
  double x1, x2, y1, y2, x, y, step, sight;
  step = 1.0 / static_cast<double>(this->precision);
  for (auto it : this->_points) {
    for (auto it2 : it->visible) {
      it->visible[it2.first] = 0;
    }
  }
  Game::Map::Node *node;
  for (auto element : *objects) {
    // sight = !day ? element->getDaySight() : element->getNightSight();
    // this->getRange(element, sight, x1, y1, x2, y2);
    // for (x = x1 ; x <= x2 ; x += step) {
    //   for (y = y1 ; y <= y2 ; y += step) {
    // 	node = this->getNode(x, y);
    // 	if (node) {
    // 	  if (this->isInSight(element, node, !day)) {
    // 	    node->visible[element->getPlayer()->getTeam()]--;
    // 	  }
    // 	}
    //   }
    // }
    sight = day ? element->getDaySight() : element->getNightSight();
    this->getRange(element, sight, x1, y1, x2, y2);
    for (x = x1 ; x <= x2 ; x += step) {
      for (y = y1 ; y <= y2 ; y += step) {
	node = this->getNode(x, y);
	if (node && this->isInSight(element, node, day)) {
	  node->visible[element->getTeam()]++;
	}
      }
    }
  }
  delete objects;
}

bool	Game::Map::move(::Game::AElement *item, ::Game::Movable *movableBase, double nx, double ny, double nz) {
  DEBUG_LOL
  ScopeLock s(this->_mutex);
  DEBUG_LOL
  if (this->_tryPosition(item, nx, ny)) {
    double ox = item->getX();
    double oy = item->getY();
    this->_remove(item, false);
    ::Game::Map::Node *node = this->getNode(nx, ny);
    if (node) {
      nz = node->z;
    }
    movableBase->setPosition(nx, ny, nz);
    this->_push(item, false);
    this->movedItemRangeAndVision(item, ox, oy);
    return (true);
  }
  return (false);
}

bool	Game::Map::hasVision(const ::Game::Team *team, double x, double y, double) const {
  ::Game::Map::Node *node = this->getNode(x, y);
  if (node) {
    if (node->visible.find(team) != node->visible.end()) {
      return (node->visible.at(team) > 0);
    }
  }
  return (false);
}

void	Game::Map::refreshUnitVisionAndRange(const ::Game::AElement *item) {
  ScopeLock s(this->_mutex);
  Vector2d left, right;
  left.x = item->getX() - item->getAttackRange() - 5.0;
  left.y = item->getY() - item->getAttackRange() - 5.0;
  right.x = item->getX() + item->getAttackRange() + 5.0;
  right.y = item->getY() + item->getAttackRange() + 5.0;
  double step = 1.0 / static_cast<double>(this->precision);
  for (double y = left.y ; y <= right.y ; y += step) {
    for (double x = left.x ; x <= right.x ; x += step) {
      Node *node = this->getNode(x, y);
      if (node) {
	if (this->isInRange(item, node)) {
	  if (std::find(node->range.begin(), node->range.end(), item) == node->range.end()) {
	    node->range.push_back(item);
	  }
	}
	else {
	  node->range.remove(item);
	}
      }
    }
  }
}

const std::map<unsigned int, std::map<unsigned int, Vector3d> > &Game::Map::getHexas(void) const {
  return (this->_hexas);
}

unsigned int	Game::Map::getHeight(unsigned int x, unsigned int y) const {
  return (static_cast<unsigned int>(this->_hexas.at(y).at(x).z));
}

unsigned int	Game::Map::getHeightAt(double x, double y) const {
  Game::Map::Node *node = this->getNode(x, y);
  if (node == NULL) {
    return (0.0);
  }
  return (static_cast<unsigned int>(node->z));
}

bool	Game::Map::isVisible(const Game::Player *player, const Game::AElement *item) const {
  if (player == NULL || item->getType() == ::Game::RESSSPOT || item->getTeam() == player->getTeam()) {
    return (true);
  }
  const Game::Team *team = player->getTeam();
  //  return (this->hasVision(team, item->getX(), item->getY(), 0.0));
  // Vector2d left, right;
  // left.x = item->getX() - item->getHitbox() - (1.0 / DOUBLE(this->precision));
  // left.y = item->getY() - item->getHitbox() - (1.0 / DOUBLE(this->precision));
  // right.x = item->getX() + item->getAttackRange() + (1.0 / DOUBLE(this->precision));
  // right.y = item->getY() + item->getAttackRange() + (1.0 / DOUBLE(this->precision));
  // double step = 1.0 / static_cast<double>(this->precision);
  // for (double y = left.y ; y <= right.y ; y += step) {
  //   for (double x = left.x ; x <= right.x ; x += step) {
  //     const Node *node = this->getNode(x, y);
  //     if (node && node->visible.find(team) != node->visible.end() && node->visible.at(team) > 0) {
  // 	return (true);
  //     }
  //   }
  // }
  const Node *node = this->getNode(item->getX(), item->getY());
  if (node) {
    if (node->visible.find(team) != node->visible.end()) {
      if (node->visible.at(team) > 0) {
	return (true);
      }
    }
  }
  return (false);
}

static const Vector3d _vv(-1.0, -1.0, -1.0);

const Vector3d &Game::Map::getHexa(unsigned int x, unsigned int y) const {
  if (this->_hexas.find(y) != this->_hexas.end()) {
    if (this->_hexas.at(y).find(x) != this->_hexas.at(y).end()) {
      return (this->_hexas.at(y).at(x));
    }
  }
  return (_vv);
}

bool	Game::Map::hexaVisible(const Game::Team *team, unsigned int x, unsigned int y) const {
  if (team == NULL) {
    return (true);
  }
  const Vector3d &hexa = this->getHexa(x, y);
  if (hexa.x <= 0) {
    return (false);
  }
  for (double ys = hexa.y ; ys < hexa.y + 2.0 * this->_hexaY ; ys += 1.0 / static_cast<double>(this->precision)) {
    for (double xs = hexa.x ; xs < hexa.x + 2.0 * this->_hexaX ; xs += 1.0 / static_cast<double>(this->precision)) {
      Node *node = this->getNode(xs, ys);
      if (node && node->visible.find(team) != node->visible.end() && node->visible.at(team) > 0) {
	return (true);
      }
    }
  }
  return (false);
}
