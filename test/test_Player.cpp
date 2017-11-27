/*
 * test_Player.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include <vector>

#include "Cell.h"
#include "gtest/gtest.h"
#include "HumanPlayer.h"
#include "Player.h"

/*
 *test flipDisks on vector of cells
 *note: this method is implemented in abstract class Player
 *I randomly chose to create Player of type HumanPlayer
 */
TEST(PlayerTest, FlipDisks) {
  vector<Cell*> cells;
  Cell* c1 = new Cell(2, 3);
  c1->insertDisk(BLACK);
  Cell* c2 = new Cell(4, 5);
  c2->insertDisk(BLACK);
  cells.push_back(c1);
  cells.push_back(c2);
  Player* pl = new HumanPlayer("tom", WHITE);
  pl->flipDisks(cells);
  for (unsigned i = 0; i < cells.size(); i++) {
    EXPECT_EQ(cells[i]->getDisk()->getColor(), WHITE);
  }
  delete c1;
  delete c2;
  delete pl;
};
