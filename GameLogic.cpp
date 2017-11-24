/*
 * GameLogic.cpp
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
 */

#include "GameLogic.h"
using namespace std;

GameLogic::GameLogic() {
}

const vector<Cell*> GameLogic::getCellsToFlip(const Board& board, int row,
    int col, Color color) {
  vector<Cell*> cells_to_flip;
  cells_to_flip.reserve(20);
  //find cells to flip in all directions
  for (int d = N; d < LAST_DIR; d++) {
    vector<Cell*> cells_d(this->cellsToFlipInDirection(board, row, col,
        color, Direction(d)));
    cells_to_flip.insert(cells_to_flip.end(), cells_d.begin(), cells_d.end());
    cells_d.clear();
  }
  return cells_to_flip;
}

const vector<Cell*> GameLogic::cellsToFlipInDirection(const Board& board,
    int row, int col, Color color, Direction dir) {
  vector<Cell*> cells_to_flip;
  cells_to_flip.reserve(6);
  Cell* next = board.getNeighboringCell(row, col, dir);
  //no disks to flip in this direction
  if (next == NULL || !next->hasDisk() ||
      next->getDisk()->getColor() == color) {
    return cells_to_flip;
  //might be disks to flip in this direction
  } else {
    while (next->getDisk()->getColor() != color) {
      cells_to_flip.push_back(next);
      int curr_row = next->getLocation().getRow();
      int curr_col = next->getLocation().getCol();
      next = board.getNeighboringCell(curr_row, curr_col, dir);
      //flip in this direction
      if (next != NULL && next->hasDisk()
          && next->getDisk()->getColor() == color) {
          break;
      //don't flip in this direction
      } else if (next == NULL || !next->hasDisk()) {
        cells_to_flip.clear();
        break;
      }
    }
    return cells_to_flip;
  }
}
