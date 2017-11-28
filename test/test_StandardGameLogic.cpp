/*
 * test_StandardGameLogic.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include "Board.h"
#include "color.h"
#include "gtest/gtest.h"
#include "StandardGameLogicTest.h"

//test getPossibleMoves in standard game logic when there are no possible moves
TEST_F(StandardGameLogicTest, NoPossibleMoves) {
  //board is empty
  Board empty_board(r_, c_);
  EXPECT_TRUE(logic_.getPossibleMoves(empty_board, BLACK).empty());
  //empty spaces but no where to go
  EXPECT_TRUE(logic_.getPossibleMoves(board_, BLACK).empty());
  //full board
  Board full_board = board_;
  for (int j = 0; j < c_; j++) {
    full_board.getCell(r_-1, j)->insertDisk(BLACK);
  }
  EXPECT_TRUE(logic_.getPossibleMoves(full_board, WHITE).empty());
};

//test getPossibleMoves in standard game logic when there are possible moves
TEST_F(StandardGameLogicTest, PossibleMoves) {
  //one possible move
  Board almost_full_board = board_;
  for (int j = 0; j < c_ - 1; j++) {
    almost_full_board.getCell(r_-1, j)->insertDisk(BLACK);
  }
  vector<Cell*> one_move;
  one_move.push_back(almost_full_board.getCell(r_-1, c_-1));
  ASSERT_EQ(logic_.getPossibleMoves(almost_full_board, WHITE).size(),
                                                    one_move.size());
  EXPECT_EQ(*logic_.getPossibleMoves(almost_full_board, WHITE)[0], *one_move[0]);
  //multiple possible moves
  vector<Cell*> mult_moves;
  mult_moves.reserve(c_);
  for (int j = 0; j < c_; j++) {
    mult_moves.push_back(board_.getCell(r_-1, j));
  }
  ASSERT_EQ(logic_.getPossibleMoves(board_, WHITE).size(), mult_moves.size());
  for (unsigned i = 0; i < logic_.getPossibleMoves(board_, WHITE).size(); i++) {
    EXPECT_EQ(*logic_.getPossibleMoves(board_, WHITE)[i], *mult_moves[i]);
  }
}
