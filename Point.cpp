/*
 * Point.cpp
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
 */

#include "Point.h"
using namespace std;

Point::Point(int row, int column) : row_(row), column_(column){
}

int Point::getCol() const {
  return column_;
}

int Point::getRow() const {
  return row_;
}

ostream& operator << (ostream &out, const Point &point) {
  out << "(" << point.row_ << "," << point.column_ << ")";
  return out;
}
