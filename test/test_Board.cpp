/*
 * test_Board.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include <vector>

#include "Board.h"
#include "BoardTest.h"
#include "color.h"
#include "gtest/gtest.h"

//test assignment of board
TEST_F(BoardTest, CheckAssigmentOverload) {
  Board b_2 = b_;
  ASSERT_EQ(b_.getRows(), b_2.getRows());
  ASSERT_EQ(b_.getCols(), b_2.getCols());
  for (int i = 0; i < b_.getRows(); i++) {
    for (int j = 0; j < b_.getCols(); j++) {
      EXPECT_EQ(*b_.getCell(i, j), *b_2.getCell(i, j));
    }
  }
}

//test if boards equal, assumes CheckAssinmentOverload works as expected
TEST_F(BoardTest, CheckEqualsOverload) {
  Board b_2 = b_;
  EXPECT_TRUE(b_2 == b_);
}

//test getCell() with out of bounds indices
TEST_F(BoardTest, GetOutOfBoundsCell) {
  EXPECT_TRUE(b_.getCell(c_*2, c_ /2) == NULL);
  EXPECT_TRUE(b_.getCell(r_/2, c_ + 1) == NULL);
}

//test getNeighboringCell with out of bound neighbors
/*SHOULD I ADD IN getNeighboringCell() return NULL if row, col are out of bounds?
* or still just return neighbor?
* if return null - then add test for that
*/
TEST_F(BoardTest, GetOutOfBoundsCellNeighbor) {
  EXPECT_TRUE(b_.getNeighboringCell(0, 0, W) == NULL);
  EXPECT_TRUE(b_.getNeighboringCell(0, 0, NW) == NULL);
  EXPECT_TRUE(b_.getNeighboringCell(0, 0, N) == NULL);
  EXPECT_TRUE(b_.getNeighboringCell(0, c_-1, NE) == NULL);
  EXPECT_TRUE(b_.getNeighboringCell(r_-1, c_-1, E) == NULL);
  EXPECT_TRUE(b_.getNeighboringCell(r_-1, c_-1, SE) == NULL);
  EXPECT_TRUE(b_.getNeighboringCell(r_-1, c_-1, S) == NULL);
  EXPECT_TRUE(b_.getNeighboringCell(r_-1, 0, SW) == NULL);
}
//test getNeighboringCell with neighbor in board
TEST_F(BoardTest, GetCellNeighbor) {
  EXPECT_EQ(*b_.getNeighboringCell(r_/2, c_/2, W), *b_.getCell(r_/2,c_/2 -1));
  EXPECT_EQ(*b_.getNeighboringCell(r_/2, c_/2, NW), *b_.getCell(r_/2 -1,c_/2 -1));
  EXPECT_EQ(*b_.getNeighboringCell(r_/2, c_/2, N), *b_.getCell(r_/2 -1,c_/2));
  EXPECT_EQ(*b_.getNeighboringCell(r_/2, c_/2, NE), *b_.getCell(r_/2 -1,c_/2 +1));
  EXPECT_EQ(*b_.getNeighboringCell(r_/2, c_/2, E), *b_.getCell(r_/2,c_/2 +1));
  EXPECT_EQ(*b_.getNeighboringCell(r_/2, c_/2, SE), *b_.getCell(r_/2 +1,c_/2 +1));
  EXPECT_EQ(*b_.getNeighboringCell(r_/2, c_/2, S), *b_.getCell(r_/2 +1,c_/2));
  EXPECT_EQ(*b_.getNeighboringCell(r_/2, c_/2, SW), *b_.getCell(r_/2 +1,c_/2 -1));
}
