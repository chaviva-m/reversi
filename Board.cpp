/*
 * Board.cpp
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
 */

#include "Board.h"
using namespace std;

Board::Board(int rows, int columns) : rows_(rows), columns_(columns) {
  this->board_ = new Cell*[this->rows_];
  for (int i = 0; i < this->rows_; i++) {
    this->board_[i] = new Cell[this->columns_];
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      this->board_[i][j] = Cell(i, j);
    }
  }
}

int Board::getRows() const {
  return this->rows_;
}

int Board::getCols() const {
  return this->columns_;
}

Cell* Board::getCell(int row, int col) const{
  if (row >= 0 && col >= 0
      && row < this->rows_ && col < this->columns_) {
    return &this->board_[row][col];
  } else {
    return NULL;
  }
}

Cell* Board::getNeighboringCell(int row, int col, Direction dir) const {

  switch(dir) {
    case N:
        return this->getCell(row - 1, col);
    case NE:
        return this->getCell(row - 1, col + 1);
    case E:
        return this->getCell(row, col + 1);
    case SE:
        return this->getCell(row + 1,col + 1);
    case S:
        return this->getCell(row + 1,col);
    case SW:
      return this->getCell(row + 1, col - 1);
    case W:
        return this->getCell(row,col - 1);
    case NW:
        return this->getCell(row - 1,col - 1);
    default:
      return NULL;
  }
}

Board::~Board() {
  for (int i = 0; i < this->rows_; i++) {
    delete[] this->board_[i];
  }
  delete this->board_;
}

ostream& operator << (ostream &out, const Board &board) {
  //first row - #s of columns
  out << " | ";
  for (int i = 0; i < board.columns_; i++) {
    out << i << " | ";
  }
  out << endl;
  for (int k = 0; k < (board.columns_ * 4 + 2); k++) {
    out << "-";
  }
  out << endl;
  //following rows - # of rows & board itself
  for (int i = 0; i < board.rows_; i++) {
    out << i << "| ";
    for (int j = 0; j < board.columns_; j++) {
      if (board.board_[i][j].hasDisk()) {
        out << board.board_[i][j].getDisk()->getColor();
      } else {
        out << " ";
      }
        out << " | ";
      }
      out << endl;
    for (int k = 0; k < (board.columns_ * 4 + 2); k++) {
      out << "-";
    }
    out << endl;
  }
  return out;
}
