//
// Vector3.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 24 16:55:48 2014 geoffrey bauduin
// Last update Fri Mar 21 11:33:42 2014 geoffrey bauduin
//

#ifndef VECTOR_HPP_
# define VECTOR_HPP_

#include	<iostream>

template<typename T>
class Vector2 {

public:
  T	x;
  T	y;

  Vector2(T xm, T ym): x(xm), y(ym) {}
  Vector2(void): x(), y() {}
  Vector2(const Vector2<T> &oth): x(oth.x), y(oth.y) {}
  virtual ~Vector2(void) {}

  Vector2<T> &operator=(const Vector2<T> &rhs) {
    this->x = rhs.x;
    this->y = rhs.y;
    return (*this);
  }

  const Vector2<T>	operator-(const Vector2<T> &rhs) const {
    Vector2<T> n;
    n.x = this->x - rhs.x;
    n.y = this->y - rhs.y;
    return (n);
  }

  Vector2<T>	&operator/=(double v) {
    this->x /= v;
    this->y /= v;
    return (*this);
  }

  Vector2<T>	&operator*=(double v) {
    this->x *= v;
    this->y *= v;
    return (*this);
  }

  bool	operator!=(const Vector2<T> &rhs) const {
    return (this->x != rhs.x || this->y != rhs.y);
  }

  T	sqLength(void) const {
    return (this->x * this->x + this->y * this->y);
  }

};

template<typename T>
class Vector3: public Vector2<T> {

public:
  T	z;

  Vector3(T xm, T ym, T zm): Vector2<T>(xm, ym), z(zm) {}
  Vector3(void): Vector2<T>(), z() {}
  Vector3(const Vector3<T> &oth): Vector2<T>(oth), z(oth.z) {}
  virtual ~Vector3(void) {}

  Vector3<T> &operator=(const Vector3<T> &rhs) {
    Vector2<T>::operator=(rhs);
    this->z = rhs.z;
    return (*this);
  }

  const Vector3<T>	operator-(const Vector3<T> &rhs) const {
    Vector2<T> n1 = Vector2<T>::operator-(rhs);
    Vector3<T> n;
    n.x = n1.x;
    n.y = n1.y;
    n.z = this->z - rhs.z;
    return (n);
  }

  Vector3<T>	&operator/=(double v) {
    Vector2<T>::operator/=(v);
    this->z /= v;
    return (*this);
  }

  Vector3<T>	&operator*=(double v) {
    Vector2<T>::operator*=(v);
    this->z *= v;
    return (*this);
  }

  bool	operator!=(const Vector3<T> &rhs) const {
    return (Vector2<T>::operator!=(rhs) || rhs.z != this->z);
  }

  T	sqLength(void) const {
    return (Vector2<T>::sqLength() + this->z * this->z);
  }

};

template<typename T>
std::ostream &operator<<(std::ostream &os, const Vector3<T> &vector) {
  os << "Vector3(" << vector.x << " ; " << vector.y << " ; " << vector.z << ")";
  return (os);
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Vector2<T> &vector) {
  os << "Vector2(" << vector.x << " ; " << vector.y << ")";
  return (os);
}

typedef Vector3<double> Vector3d;
typedef Vector2<double>	Vector2d;
typedef Vector2<int>	Vector2i;

#endif
