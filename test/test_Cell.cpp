/*
 * test_Cell.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include "Cell.h"
#include "CellTest.h"
#include "color.h"
#include "gtest/gtest.h"

//tests assignment of cell
TEST_F(CellTest, CheckAssignmentOverload) {
  Cell c = c_;
  EXPECT_EQ(c_.getLocation().getRow(), c.getLocation().getRow());
  EXPECT_EQ(c_.getLocation().getCol(), c.getLocation().getCol());
  EXPECT_EQ(*c_.getDisk(), *c.getDisk());
}

//checks if cells equal or unequal
TEST_F(CellTest, CheckEqualsOverload) {
  //equal cell
  Cell c1 = c_;
  EXPECT_EQ(c1, c_);
  //cell with different location but same disk color
  Cell c2(c_.getLocation().getRow()-1, c_.getLocation().getCol());
  c2.insertDisk(c_.getDisk()->getColor());
  EXPECT_NE(c2, c_);
  //cell with same location but no disk
  Cell c3(c_.getLocation().getRow(), c_.getLocation().getCol());
  EXPECT_NE(c3, c_);
}
