/*
 * Printers.cpp
 *
 * Author: djoffe
 * Dana Joffe
 * ID 312129240
 */

#include "Printers.h"

Printer::~Printer() {}
ConsolePrinter::ConsolePrinter() {}
ConsolePrinter::~ConsolePrinter() {}

ConsolePrinter* ConsolePrinter::clone () const {
	return new ConsolePrinter(*this);
}
void ConsolePrinter::printBoard(const Board& board) const {
	cout << board;
}
void ConsolePrinter::printMessage(const string& message, Location loc) const {
	cout << message;
}

