/*
 * test_IAPlayer.cpp
 *
 *  Created on: Nov 25, 2017
 *      Author: chaviva
 */

#include "AIPlayer.h"
#include "AIPlayerTest.h"
#include "Board.h"
#include "gtest/gtest.h"
#include "StandardGameLogic.h"

//choose move that will give rival negative min scoring
TEST_F(AIPlayerTest, ChooseMoveWithNegRivalMinScore) {
  vector<Cell*> possible_moves(logic_.getPossibleMoves(board_rival_negative_,
                                                              WHITE));
  Point AI_choice = a_i_player_.decideOnAMove(board_rival_negative_,
                      possible_moves, logic_);
  EXPECT_EQ(AI_choice, Point(3,0));
}

//choose move that will give rival positive min scoring
TEST_F(AIPlayerTest, ChooseMoveWithPosRivalMinScore) {
  vector<Cell*> possible_moves(logic_.getPossibleMoves(board_rival_positive_,
                                                              WHITE));
  Point AI_choice = a_i_player_.decideOnAMove(board_rival_positive_,
                      possible_moves, logic_);
  EXPECT_EQ(AI_choice, Point(0,3));
}

//choose move that will give rival no possible moves
TEST_F(AIPlayerTest, ChooseMoveWithNoPossibleMovesForRival) {
  vector<Cell*> possible_moves(logic_.getPossibleMoves(board_rival_no_moves_,
                                                              WHITE));
  Point AI_choice = a_i_player_.decideOnAMove(board_rival_no_moves_,
                      possible_moves, logic_);
  EXPECT_EQ(AI_choice, Point(3, 0));
}
