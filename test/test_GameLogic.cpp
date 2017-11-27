/*
 * test_GameLogic.cpp
 *
 *  Created on: Nov 25, 2017
 *      Author: chaviva
 */
#include <map>
#include <vector>

#include "Board.h"
#include "color.h"
#include "GameLogic.h"
#include "GameLogicTest.h"
#include "gtest/gtest.h"

//test getCellsToFlip in game logic with move that won't flip any cells
TEST_F(GameLogicTest, NoCellsToFlip) {
  //move near blank spaces
  EXPECT_TRUE(logic_->getCellsToFlip(board_, 0, 1, WHITE).empty());
  //move near same color
  EXPECT_TRUE(logic_->getCellsToFlip(board_, 5, 3, WHITE).empty());
  //move near rival's color that ends in blanks & edge of board
  EXPECT_TRUE(logic_->getCellsToFlip(board_, 2, 4, WHITE).empty());
}

//test getCellsToFlip in game logic with move that will flip cells
TEST_F(GameLogicTest, GetCellsToFlip) {
  //move will flip neighbors in one direction
  vector<Cell*> flip_1_dir;
  flip_1_dir.push_back(board_.getCell(3, 3));
  ASSERT_EQ(logic_->getCellsToFlip(board_, 2, 3, WHITE).size(),
                                            flip_1_dir.size());
  EXPECT_EQ(logic_->getCellsToFlip(board_, 2, 3, WHITE)[0], flip_1_dir[0]);
  //move will flip neighbors in multiple directions
  vector<Cell*> flip_mult_dir;
  flip_mult_dir.push_back(board_.getCell(4, 2));
  flip_mult_dir.push_back(board_.getCell(4, 3));
  EXPECT_EQ(logic_->getCellsToFlip(board_, 5, 2, BLACK).size(),
                                          flip_mult_dir.size());
  for (unsigned i = 0; i < flip_mult_dir.size(); i++) {
    EXPECT_EQ(logic_->getCellsToFlip(board_, 5, 2, BLACK)[i], flip_mult_dir[i]);
  }
}

//test getScores in game logic when there are no disks of color
TEST_F(GameLogicTest,CheckScoreZero) {
  //check score when no disks are on board
  Board board(8, 8);
  EXPECT_EQ(logic_->getScores(board).find(WHITE)->second, 0);
  EXPECT_EQ(logic_->getScores(board).find(BLACK)->second, 0);
  //check score when one color's score is 0
  board.getCell(3, 4)->insertDisk(WHITE);
  EXPECT_EQ(logic_->getScores(board).find(BLACK)->second, 0);
}

//test getScores in game logic when scores are positive
TEST_F(GameLogicTest, CheckPositiveScores) {
  //board with unequal scores
  EXPECT_EQ(logic_->getScores(board_).find(WHITE)->second, 2);
  EXPECT_EQ(logic_->getScores(board_).find(BLACK)->second, 8);
  //board is full and tied
  Board full_board(4, 4);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      board_.getCell(i, j)->insertDisk(BLACK);
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 2; j < 4; j++) {
      board_.getCell(i, j)->insertDisk(WHITE);
    }
  }
  EXPECT_EQ(logic_->getScores(full_board).find(WHITE)->second, 8);
  EXPECT_EQ(logic_->getScores(full_board).find(BLACK)->second, 8);
}
