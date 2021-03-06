/*
 * Cell.h
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#ifndef CELL_H_
#define CELL_H_

#include "color.h"
#include "Disk.h"
#include "Point.h"
#include "iostream"
using namespace std;

/**
 * cell in specific location in board.
 * can be empty or can hold disk.
 */
class Cell {
public:
  /**
   * constructs cell with row & column
   * input: int row (default: 0), int column (default: 0)
   * output: void
   */
  Cell(int row = 0, int column = 0);
  /*
   * copy constructor.
   */
  Cell(const Cell &oldCell);

  /*
   * assignment cell.
   * reset this cell with newCell.
   */
  Cell& operator=(const Cell& newCell) {
    if (this != &newCell) {
      delete this->disk_;
      // Copy the inherited part
      if (newCell.isEmpty_) {
    	  disk_  = NULL;
      } else {
    	  insertDisk(newCell.getDisk()->getColor());
      }
      location_ = Point(newCell.getLocation().getRow(),
      		newCell.getLocation().getCol());
    }
    return *this;
  }

  /**
  * return true if the cells have the same points and the same disk.
  */
  bool operator ==(const Cell& cell) const;
  /**
  * return true if the cells are unequal
  */
  bool operator !=(const Cell &cell) const;

  /**
   * access location of cell
   * input: void
   * output: Point location
   */
  Point getLocation() const;
  /**
   * return true if cell holds disk, false if empty
   * input: void
   * output: true if cell has disk, otherwise false
   */
  bool hasDisk() const;
  /**
   * insert disk of color in cell
   * input: Color color
   * output: void
   */
  void insertDisk(Color color);
  /**
   * access disk in cell
   * input: void
   * output: Disk* disk in cell
   */
  Disk* getDisk() const;
  /**
   * destructs cell
   * input: void
   * output: void
   */
  ~Cell();

private:
  Point location_;
  Disk *disk_;
  bool isEmpty_;
};

#endif /* CELL_H_ */
