/*
 * GameLogic.h
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
 */

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

#include <vector>
#include "Board.h"
#include "color.h"
#include <map>


/**
 * supplies game logic according to game rules.
 * abstract class.
 */
class GameLogic {
public:
  /**
   * constructs game logic
   * input: void
   * output: void
   */
  GameLogic();
  /**
   * return player's (of color) possible moves in board
   * input: Board& board, Color color
   * output: std::vector<Cell*> cells of possible moves
   */
  virtual const std::vector<Cell*>
  getPossibleMoves(const Board& board, Color color) = 0;
  /**
   * return cells on board that will flip bc of player's insertion of color
   * disk in (row,col) location of board
   * input: Board& board, int row, int col, Color color
   * output: std::vector<Cell*> cells to flip
   */
  const std::vector<Cell*> getCellsToFlip(const Board& board,
                    int row, int col, Color color);
  /*
   * calculates which cells are supposed to be have their disk flipped in all directions,
   * after a disk of color <color> has been inserted at (row, col) in <board>.
   * input: board- current game board.
   *		   row, col - the new disk's location on board.
   *		   color - the new disk's color.
   * output: a vector of cells that their disk should be flipped.
   */
  const std::vector<Cell*> getCellsToFlip(const Board& board,
                    Point p, Color color);
  /*
   * return a map that connects the player's color to his score.
   * the score of player X is the amount of disks he has on the board.
   * input: board - the current board.
   */
  const map<Color, int> getScores(const Board& board);
  /**
   * destructs game logic
   * input: void
   * output: void
   */
  virtual ~GameLogic() {};

private:
  /*
  * calculates which cells are supposed to be have their disk flipped in a specific direction
  * after a disk of color <color> has been inserted at (row, col) in <board>.
  * input: board- current game board.
  *		   row, col - the new disk's location on board.
  *		   color - the new disk's color.
  *		   dir - the direction that should be checked.
  * output: a vector of cells that their disk should be flipped.
  */
  const std::vector<Cell*> cellsToFlipInDirection(const Board& board, int row,
      int col, Color color, Direction dir);
};

#endif /* GAMELOGIC_H_ */
