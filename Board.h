/*
 * Board.h
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>

#include "Cell.h"

//directions in board
enum Direction {N, NE, E, SE, S, SW, W, NW, LAST_DIR};

/**
 * board of game
 * holds matrix (rows x columns) of cells
 */
class Board {
public:
  /**
   * constructs Board of rows x columns
   * input: int rows (default: 0), int columns (default: 0)
   * output: void
   */
  Board(int rows = 0, int columns = 0);

  // copy constructor
  Board(const Board &oldBoard);

  //Assignment Board
  Board& operator=(const Board& oldBoard) {
//	  cout <<endl <<"~~~Assignment Board~~~"<<endl;

    if (this != &oldBoard) {
      if (this->rows_!= oldBoard.getRows() || this->columns_!= oldBoard.getCols()) {
    	cout << "Could not make Board Assignment. Sizes don't match"<<endl;
      	return *this;
      }
//      for (int i = 0; i < this->rows_; i++) {
//        delete[] this->board_[i];
//      }
//      for (int i = 0; i < this->rows_; i++) {
//        for (int j = 0; j < this->rows_; j++) {
//        	delete this->board_[i][j];
//     	}
//      }


      // Copy the inherited part
      for (int i = 0; i < this->rows_; i++) {
    	  for (int j = 0; j < this->rows_; j++) {
    		  this->board_[i][j] = *oldBoard.getCell(i, j);
    	  }
      }
    }
    return *this;
  }

  /**
   * access # of rows of board
   * input: void
   * output: int rows
   */
  int getRows() const;
  /**
   * access # of columns of board
   * input: void
   * output: int columns
   */
  int getCols() const;
  /**
   * access cell in (row,col) location of board
   * input: int row, int col
   * output: Cell* cell
   */
  Cell* getCell(int row, int col) const;
  /**
  * access cell in p location of board
  * input: point p
  * output: Cell* cell in the point p
  */
  Cell* getCell(Point p) const;

  /**
   * access neighbor of cell of (row,col) location, in dir direction
   * input: int row, int col, Direction dir
   * output: Cell* neighboring cell
   */
  Cell* getNeighboringCell(int row, int col, Direction dir) const;
  /**
   * destructs board
   * input: void
   * output: void
   */
  ~Board();
  /**
   * board output
   * input: std::ostream &out, const Board &board
   * output: std::ostream& outputboard
   */
  friend std::ostream& operator << (std::ostream &out, const Board &board);

private:
  int rows_;
  int columns_;
  Cell** board_;
};

#endif /* BOARD_H_ */
