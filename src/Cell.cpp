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

Cell::Cell(const Cell &oldCell) : location_(oldCell.getLocation().getRow(),
		oldCell.getLocation().getCol()) {
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

bool Cell::operator ==(const Cell &cell) const {
  bool same_disk = false;
  if (this->hasDisk() && cell.hasDisk()) {
    same_disk = (*disk_ == *cell.getDisk());
  } else {
    same_disk = (this->hasDisk() == cell.hasDisk());
  }
  return (location_.getRow() == cell.getLocation().getRow() &&
          location_.getCol() == cell.getLocation().getCol() &&
          same_disk);
}

bool Cell::operator !=(const Cell &cell) const {
  return !(*this == cell);
}

Cell::~Cell() {
  delete this->disk_;
}
