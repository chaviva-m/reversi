/*
 * Cell.cpp
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
 */

#include "Cell.h"

Cell::Cell(int row, int column) : location_(row, column), disk_(NULL),
              isEmpty_(true) {
}

//Copy c'tor Cell
Cell::Cell(const Cell &oldCell) : location_(oldCell.getLocation().getRow(),
		oldCell.getLocation().getCol()) {
	cout <<endl <<"~~~Copy c'tor Cell~~~"<<endl;

  if (oldCell.hasDisk()) {
	  insertDisk(oldCell.getDisk()->getColor());
  } else {
	  disk_ = NULL;
	  isEmpty_ = true;
  }
}


Point Cell::getLocation() const {
  return this->location_;
}

bool Cell::hasDisk() const {
  return !this->isEmpty_;
}

void Cell::insertDisk(Color color) {
  this->disk_ = new Disk(color);
  this->isEmpty_ = false;
}

Disk* Cell::getDisk() const {
  return this->disk_;
}

Cell::~Cell() {
  delete this->disk_;
}
