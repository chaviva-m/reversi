/*
 * CellTest.h
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include "Cell.h"
#include "color.h"
#include "gtest/gtest.h"

/*
 * Test fixture for CellTest.
 * class holds cell
 */
class CellTest: public testing::Test {
public:
  CellTest() : c_(0, 100) {};
  virtual void SetUp() {
    c_.insertDisk(BLACK);
  };
  virtual void TearDown() {};

protected:
  Cell c_;

};



