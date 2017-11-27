/*
 * BoardTest.cpp
 *
 *  Created on: Nov 25, 2017
 *      Author: chaviva
 */

#include "Board.h"
#include "color.h"
#include "gtest/gtest.h"

class BoardTest: public testing::Test {
public:
  BoardTest() : r_(8), c_(8), b_(Board(r_, c_)) {};
  virtual void SetUp() {
    b_.getCell(3, 4)->insertDisk(WHITE);
    b_.getCell(4, 3)->insertDisk(WHITE);
    b_.getCell(3, 3)->insertDisk(BLACK);
    b_.getCell(4, 4)->insertDisk(BLACK);
  }
  virtual void TearDown() {
    //delete b_;
  };
  Board b_;
  int r_;
  int c_;
};


