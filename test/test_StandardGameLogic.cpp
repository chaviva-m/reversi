/*
 * test_StandardGameLogic.cpp
 *
 *  Created on: Nov 25, 2017
 *      Author: chaviva
 */

#include "Board.h"
#include "color.h"
#include "gtest/gtest.h"
#include "StandardGameLogicTest.h"
/*
 * CANT ACTUALLY CHECK IF VECTORS EQUAL THIS WAY
 */

//test getPossibleMoves in standard game logic when there are no possible moves
TEST_F(StandardGameLogicTest, NoPossibleMoves) {
  //empty spaces but no where to go
  EXPECT_TRUE(logic_.getPossibleMoves(board_, BLACK).empty());
  //full board
  Board full_board = board_;
  for (int j = 0; j < 4; j++) {
    full_board.getCell(3, j)->insertDisk(BLACK);
  }
  EXPECT_TRUE(logic_.getPossibleMoves(board_, WHITE).empty());
};

//test getPossibleMoves in standard game logic when there are possible moves
TEST_F(StandardGameLogicTest, PossibleMoves) {
  vector<Cell*> moves;
  moves.reserve(4);
  for (int j = 0; j < 4; j++) {
    moves.push_back(board_.getCell(3, j));
  }
  ASSERT_EQ(logic_.getPossibleMoves(board_, WHITE).size(), moves.size());
  for (int i = 0; i < logic_.getPossibleMoves(board_, WHITE).size(); i++) {
    EXPECT_EQ(logic_.getPossibleMoves(board_, WHITE)[i], moves[i]);
  }
}
