/*
 * StandardGameLogic.cpp
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
 */

#include "StandardGameLogic.h"
using namespace std;

StandardGameLogic::StandardGameLogic() {}

const vector<Cell*> StandardGameLogic::getPossibleMoves(const Board& board,
    Color color) {
  vector<Cell*> possible_moves;
  possible_moves.reserve(15);
  bool flip_dir = false;
  //loop through all cells in board
  for (int i = 0; i < board.getRows(); i++) {
    for (int j = 0; j < board.getCols(); j++) {
      //check in all directions if move will flip cells
      for (int d = N; d < LAST_DIR; d++) {
        flip_dir = flipInDirection(board, i, j, Direction(d), color);
        if (flip_dir) {
          possible_moves.push_back(board.getCell(i,j));
          break;
        }
      }
    }
  }
  return possible_moves;
}

bool StandardGameLogic::flipInDirection(const Board& board,
    int row, int col, Direction dir, Color color) {
  //cell is taken
  if (board.getCell(row, col)->hasDisk()) {
    return false;
  }
  //neighbor is empty or its neighbor is empty/same color
  Cell* next = board.getNeighboringCell(row, col, dir);
  if (next == NULL || !next->hasDisk() ||
      next->getDisk()->getColor() == color) {
    return false;
  //need to continue checking in this direction
  } else {
    while (next != NULL && next->hasDisk()
        && next->getDisk()->getColor() != color) {
      int curr_row = next->getLocation().getRow();
      int curr_col = next->getLocation().getCol();
      next = board.getNeighboringCell(curr_row, curr_col, dir);
      if (next != NULL && next->hasDisk()
          && next->getDisk()->getColor() == color) {
          return true;
      }
    }
    return false;
  }
}

StandardGameLogic::~StandardGameLogic() {}
