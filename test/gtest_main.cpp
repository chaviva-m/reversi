/*
 * gtest_main.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: chaviva
 */

#include "gtest/gtest.h"

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


