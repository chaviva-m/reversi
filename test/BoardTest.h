/*
 * BoardTest.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include "Board.h"
#include "color.h"
#include "gtest/gtest.h"

/*
 * Test fixture for BoardTest.
 * class holds board & board dimensions.
 */
class BoardTest: public testing::Test {
public:
  BoardTest() : r_(8), c_(8), b_(Board(r_, c_)) {};
  virtual void SetUp() {
    b_.getCell(3, 4)->insertDisk(WHITE);
    b_.getCell(4, 3)->insertDisk(WHITE);
    b_.getCell(3, 3)->insertDisk(BLACK);
    b_.getCell(4, 4)->insertDisk(BLACK);
  }
  virtual void TearDown() {};

protected:
  int r_;
  int c_;
  Board b_;
};



