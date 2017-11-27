/*
 * Disk.cpp
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
 */

#include "Disk.h"
using namespace std;

Disk::Disk(Color color) : color_(color){
}

Color Disk::getColor() const {
	return this->color_;
}

void Disk::flipDisk() {
  switch (this->color_) {
    case BLACK:
      this->color_ = WHITE;
      break;
    case WHITE:
      this->color_ = BLACK;
      break;
    default:
      break;
  }
}
