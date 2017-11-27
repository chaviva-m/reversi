/*
 * StandardGameLogicTest.h
 *
 *  Created on: Nov 26, 2017
 *      Author: chaviva
 */

#include "Board.h"
#include "gtest/gtest.h"
#include "StandardGameLogic.h"

class StandardGameLogicTest : public testing::Test {
public:
  StandardGameLogicTest() : logic_(StandardGameLogic()), board_(Board(4,4)) {};
  virtual void SetUp() {
    for (int j = 0; j < 4; j++) {
      board_.getCell(0, j)->insertDisk(WHITE);
    }
    for (int i = 1; i < 3; i++) {
      for (int j = 0; j < 4; j++) {
        board_.getCell(0, j)->insertDisk(BLACK);
      }
    }
  };
  virtual void TearDown() {};

protected:
  StandardGameLogic logic_;
  Board board_;
};
