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

class GameLogicTest: public testing::Test {
public:
  GameLogicTest() : board_(Board(8,8)), logic_(new StandardGameLogic()){};
  virtual void SetUp() {
    board_.getCell(4, 2)->insertDisk(WHITE);
    board_.getCell(4, 3)->insertDisk(WHITE);
    board_.getCell(3, 2)->insertDisk(BLACK);
    board_.getCell(3, 3)->insertDisk(BLACK);
    board_.getCell(3, 4)->insertDisk(BLACK);
    board_.getCell(3, 5)->insertDisk(BLACK);
    board_.getCell(4, 4)->insertDisk(BLACK);
    board_.getCell(4, 5)->insertDisk(BLACK);
    board_.getCell(4, 6)->insertDisk(BLACK);
    board_.getCell(4, 7)->insertDisk(BLACK);
  };
  virtual void TearDown() {
    delete logic_;
  };

protected:
  Board board_;
  GameLogic* logic_;
};
