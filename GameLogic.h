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
  /**
   * destructs game logic
   * input: void
   * output: void
   */
  virtual ~GameLogic() {};

private:
  /**
   * find cells to flip on board in dir direction from insertion of color disk
   * in (row,col) location of board
   * input: Board& board, int row, int col, Color color, Direction dir
   * output:
   */
  const std::vector<Cell*> cellsToFlipInDirection(const Board& board, int row,
      int col, Color color, Direction dir);
};

#endif /* GAMELOGIC_H_ */
