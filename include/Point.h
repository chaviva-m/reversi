/*
 * Point.h
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include <sstream>
#include <string>

/**
 * point of specified row,column
 */
class Point {
public:
  /**
   * constructs point
   * input: int row, int column
   * output: void
   */
  Point(int row=-1, int column=-1);
  /**
   * access column coordinate of point
   * input: void
   * output: void
   */
  int getCol() const;
  /**
   * access row coordinate of point
   * input: void
   * output: void
   */
  int getRow() const;
  /**
   * return true if points are equal.
   */
  bool operator ==(const Point &point) const;
  /**
   * return true if points are unequal.
   */
  bool operator !=(const Point &point) const;
  /**
   * point output
   * input: std::ostream &out, const Point &point
   * output: std::ostream& output
   */
  friend std::ostream& operator << (std::ostream &out, const Point &point);


private:
  int row_;
  int column_;
};

#endif /* POINT_H_ */
