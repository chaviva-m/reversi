/*
 * ConsolePrinter.cpp
 *
 *  Created on: Nov 20, 2017
 *      Author: chaviva
 */

#include "ConsolePrinter.h"
using namespace std;

ConsolePrinter::ConsolePrinter() {}
ConsolePrinter::~ConsolePrinter() {}

ConsolePrinter* ConsolePrinter::clone () const {
  return new ConsolePrinter(*this);
}
void ConsolePrinter::printBoard(const Board& board) const {
  cout << board;
}
void ConsolePrinter::printMessage(const string& message, Point loc) const {
  cout << message;
}
