/*
 * StandardGameLogic.h
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
 */

#ifndef STANDARDGAMELOGIC_H_
#define STANDARDGAMELOGIC_H_

#include <vector>
#include "Board.h"
#include "color.h"
#include "GameLogic.h"

/**
 * supplies game logic according to standard game rules
 */
class StandardGameLogic: public GameLogic {
public:
  /**
   * constructs game logic
   * input: void
   * output: void
   */
  StandardGameLogic();
  /*
   *
   */
  virtual const std::vector<Cell*> getPossibleMoves(const Board& board,
      Color color);
  /*
   * destructor.
   */
  virtual ~StandardGameLogic();

private:
  /**
   * check if insertion in (row,col) will flip neighboring disks
   * input: const Board& board, int row, int col, Direction dir, Color color
   * output: true if flip in this direction, otherwise false
   */
  bool flipInDirection(const Board& board, int row, int col,
                        Direction dir, Color color);
};

#endif /* STANDARDGAMELOGIC_H_ */
