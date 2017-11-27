/*
 * StandardGameLogicTest.h
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include "Board.h"
#include "gtest/gtest.h"
#include "StandardGameLogic.h"

/*
 * Test fixture for StandardGameLogicTest
 * class holds StandardGameLogic, board & board dimensions.
 */
class StandardGameLogicTest : public testing::Test {
public:
  StandardGameLogicTest() : r_(4), c_(4), logic_(StandardGameLogic()),
                            board_(Board(r_,c_)) {};
  virtual void SetUp() {
    for (int j = 0; j < c_; j++) {
      board_.getCell(0, j)->insertDisk(WHITE);
    }
    for (int i = 1; i < 3; i++) {
      for (int j = 0; j < c_; j++) {
        board_.getCell(i, j)->insertDisk(BLACK);
      }
    }
  };
  virtual void TearDown() {};

protected:
  int r_;
  int c_;
  StandardGameLogic logic_;
  Board board_;
};
