/*
 * ConsolePrinter.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
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
