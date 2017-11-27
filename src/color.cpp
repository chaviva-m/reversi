/*
 * color.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include "color.h"

std::ostream& operator <<(std::ostream &out, const Color &color) {
  switch(color) {
      case BLACK:
        return out << "X";
      case WHITE:
        return out << "O";
      default:
        return out;
    }
}



