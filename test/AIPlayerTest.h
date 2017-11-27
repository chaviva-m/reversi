/*
 * IAPlayerTest.h
 *
 *  Created on: Nov 26, 2017
 *      Author: chaviva
 */

#include "AIPlayer.h"
#include "Board.h"
#include "gtest/gtest.h"
#include "StandardGameLogic.h"

class AIPlayerTest : public testing::Test {
public:
  AIPlayerTest() : logic_(StandardGameLogic()),
    a_i_player_(AIPlayer("AI", WHITE)), board_rival_negative(Board(4, 4)),
    board_rival_positive(Board(4,4)), board_rival_no_moves(Board(4,4)) {};
  virtual void SetUp() {
    //board in which possible moves for human after possible moves for AI
    //will all have NEGATIVE minRivalScoring
    boardWithNegMinRivalScoring();
    //board in which possible moves for human after possible moves for AI
    //will all have POSTIVE minRivalScoring
    boardWithPosMinRivalScoring();
    //board in which human will have no possible moves after possible move of AI
    boardWithNoMovesForRival();
  };
  void boardWithNegMinRivalScoring() {
    board_rival_negative.getCell(0, 0)->insertDisk(BLACK);
    for (int j = 1; j < 4; j++) {
      board_rival_negative.getCell(0, j)->insertDisk(WHITE);
    }
    for (int j = 0; j < 4; j++) {
        board_rival_negative.getCell(1, j)->insertDisk(WHITE);
    }
    board_rival_negative.getCell(2, 0)->insertDisk(BLACK);
    board_rival_negative.getCell(2, 1)->insertDisk(BLACK);
  };
  void boardWithPosMinRivalScoring() {
    board_rival_positive.getCell(1,1)->insertDisk(BLACK);
    for (int i = 0; i < 3; i++) {
      board_rival_positive.getCell(i, 2)->insertDisk(BLACK);
    }
    board_rival_positive.getCell(2,1)->insertDisk(BLACK);
  };
  void boardWithNoMovesForRival() {
    board_rival_no_moves.getCell(0,0)->insertDisk(WHITE);
    board_rival_no_moves.getCell(0,1)->insertDisk(WHITE);
    board_rival_no_moves.getCell(1,0)->insertDisk(WHITE);
    board_rival_no_moves.getCell(1,1)->insertDisk(BLACK);
    board_rival_no_moves.getCell(2,0)->insertDisk(BLACK);
  };
  virtual void TearDown() {};

protected:
  StandardGameLogic logic_;
  AIPlayer a_i_player_;
  Board board_rival_negative;
  Board board_rival_positive;
  Board board_rival_no_moves;
};




