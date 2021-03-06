/*
 * Point.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
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
  out << "(" << point.row_+1 << "," << point.column_ +1 << ")";
  return out;
}

bool Point::operator ==(const Point& point) const {
  return (row_ == point.getRow() && column_ == point.getCol());
}

bool Point::operator !=(const Point& point) const {
  return !(*this == point);
}
