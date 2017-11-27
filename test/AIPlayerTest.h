/*
 * IAPlayerTest.h
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include "AIPlayer.h"
#include "Board.h"
#include "gtest/gtest.h"
#include "StandardGameLogic.h"

/*
 * test fixture for AIPlaTest.
 * class holds standardGameLogic, 3 boards & board dimensions
 */
class AIPlayerTest : public testing::Test {
public:
  AIPlayerTest() : r_(4), c_(4), logic_(StandardGameLogic()),
    a_i_player_(AIPlayer("AI", WHITE)), board_rival_negative_(Board(r_, c_)),
    board_rival_positive_(Board(r_, c_)), board_rival_no_moves_(Board(r_, c_)) {};
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
    board_rival_negative_.getCell(0, 0)->insertDisk(BLACK);
    for (int j = 1; j < 4; j++) {
      board_rival_negative_.getCell(0, j)->insertDisk(WHITE);
    }
    for (int j = 0; j < 4; j++) {
        board_rival_negative_.getCell(1, j)->insertDisk(WHITE);
    }
    board_rival_negative_.getCell(2, 0)->insertDisk(BLACK);
    board_rival_negative_.getCell(2, 1)->insertDisk(BLACK);
  };
  void boardWithPosMinRivalScoring() {
    board_rival_positive_.getCell(1,1)->insertDisk(BLACK);
    for (int i = 0; i < 3; i++) {
      board_rival_positive_.getCell(i, 2)->insertDisk(BLACK);
    }
    board_rival_positive_.getCell(2,1)->insertDisk(WHITE);
  };
  void boardWithNoMovesForRival() {
    board_rival_no_moves_.getCell(0,0)->insertDisk(WHITE);
    board_rival_no_moves_.getCell(0,1)->insertDisk(WHITE);
    board_rival_no_moves_.getCell(1,0)->insertDisk(WHITE);
    board_rival_no_moves_.getCell(1,1)->insertDisk(BLACK);
    board_rival_no_moves_.getCell(2,0)->insertDisk(BLACK);
  };
  virtual void TearDown() {};

protected:
  int r_;
  int c_;
  StandardGameLogic logic_;
  AIPlayer a_i_player_;
  Board board_rival_negative_;
  Board board_rival_positive_;
  Board board_rival_no_moves_;
};




