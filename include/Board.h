/*
 * Board.h
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
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
   /*
   * copy constructor.
   */
  Board(const Board &oldBoard);
  /*
   * assignment board.
   * reset this board with newBoard.
   */
  Board& operator=(const Board& newBoard);
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
   * returns true if board is equal to this
   */
  bool operator ==(const Board& board) const;
  /**
   * returns true if board is unequal to this
   */
  bool operator !=(const Board& board) const;
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
