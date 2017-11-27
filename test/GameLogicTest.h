/*
 * GameLogicTest.h
 *
 *  Created on: Nov 26, 2017
 *      Author: chaviva
 */

#include "Board.h"
#include "GameLogic.h"
#include "gtest/gtest.h"
#include "StandardGameLogic.h"

/*
 * Test fixture for GameLogicTest
 * class holds GameLogic, 2 boards & board dimensions.
 */
class GameLogicTest: public testing::Test {
public:
  GameLogicTest() : r_(8), c_(8), board_(Board(r_,c_)),
    board_full(Board(r_,c_)), logic_(new StandardGameLogic()){};
  virtual void SetUp() {
    setUpBoard();
    setUpFullBoard();
  };

  void setUpBoard() {
    board_.getCell(4, 2)->insertDisk(WHITE);
    board_.getCell(4, 3)->insertDisk(WHITE);
    board_.getCell(3, 2)->insertDisk(BLACK);
    board_.getCell(3, 3)->insertDisk(BLACK);
    board_.getCell(3, 4)->insertDisk(BLACK);
    board_.getCell(3, 5)->insertDisk(BLACK);
    board_.getCell(4, 4)->insertDisk(BLACK);
    board_.getCell(4, 5)->insertDisk(BLACK);
    board_.getCell(2, 4)->insertDisk(BLACK);
    board_.getCell(1, 4)->insertDisk(BLACK);
    board_.getCell(0, 4)->insertDisk(BLACK);
  }

  void setUpFullBoard() {
    for (int i = 0; i < r_; i++) {
      for (int j = 0; j < c_/2; j++) {
        board_full.getCell(i, j)->insertDisk(BLACK);
      }
    }
    for (int i = 0; i < r_; i++) {
      for (int j = c_/2; j < c_; j++) {
        board_full.getCell(i, j)->insertDisk(WHITE);
      }
    }
  }

  virtual void TearDown() {
    delete logic_;
  };

protected:
  int r_;
  int c_;
  Board board_;
  Board board_full;
  GameLogic* logic_;
};
