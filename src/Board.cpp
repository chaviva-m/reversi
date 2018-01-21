/*
 * Board.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
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

Board::Board(const Board &oldBoard) : rows_(oldBoard.getRows()),
		columns_(oldBoard.getCols())  {
    this->board_ = new Cell*[this->rows_];
	for (int i = 0; i < this->rows_; i++) {
	  this->board_[i] = new Cell[this->columns_];
	}
	for (int i = 0; i < rows_; i++) {
	  for (int j = 0; j < columns_; j++) {
	    this->board_[i][j] = *oldBoard.getCell(i, j);
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

Cell* Board::getCell(Point p) const{
  return this->getCell(p.getRow(), p.getCol());
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
  delete[] this->board_;
}

ostream& operator << (ostream &out, const Board &board) {
  //first row - #s of columns
  out << " | ";
  for (int i = 0; i < board.columns_; i++) {
    out << i+1 << " | ";
  }
  out << endl;
  for (int k = 0; k < (board.columns_ * 4 + 2); k++) {
    out << "-";
  }
  out << endl;
  //following rows - # of rows & board itself
  for (int i = 0; i < board.rows_; i++) {
    out << i+1 << "| ";
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

bool Board::operator ==(const Board& board) const {
  if (rows_ == board.getRows() && columns_ == board.getCols()) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < columns_; j++) {
        if (*getCell(i, j) != *board.getCell(i, j)) {
          return false;
        }
      }
    }
    return true;
  } else {
    return false;
  }
}

bool Board::operator !=(const Board& board) const {
  return !(*this == board);
}

Board& Board::operator=(const Board& newBoard) {
  if (this != &newBoard) {
    if (this->rows_!= newBoard.getRows() || this->columns_!= newBoard.getCols()) {
      cout << "Could not make Board Assignment. Sizes don't match"<<endl;
      return *this;
    }
    //delete old information.
    for (int i = 0; i < this->rows_; i++) {
      delete[] this->board_[i];
    }
    delete[] this->board_;
    //initialize new information.
    this->board_ = new Cell*[this->rows_];
    for (int i = 0; i < this->rows_; i++) {
      this->board_[i] = new Cell[this->columns_];
    }
    // Copy the inherited part
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->rows_; j++) {
        this->board_[i][j] = *newBoard.getCell(i, j);
      }
    }
  }
  return *this;
}
