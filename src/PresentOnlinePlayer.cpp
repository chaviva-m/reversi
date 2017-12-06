/*
 * PresentOnlinePlayer.cpp
 *
 *  Created on: Dec 6, 2017
 *      Author: chaviva
 */

#include "PresentOnlinePlayer.h"
using namespace message;

PresentOnlinePlayer::PresentOnlinePlayer(const std::string& name, Color color,
    CommunicationChannel& channel) :
    HumanPlayer(name, color), channel_(channel) {}

void PresentOnlinePlayer::endTurn(Point* move, Printer& printer) const {
  if (move == NULL) {
    sendStatus(NO_MOVES, printer);
  } else {
	sendStatus(HAS_MOVE, printer);
	sendMove(move->getRow(), move->getCol(), printer);
  }
}


void PresentOnlinePlayer::sendStatus(int stat, Printer& printer) const {
  int n = write(channel_.getClientSocket(), &stat, sizeof(stat));
  if (n == -1) {
	printer.printMessage(errorWritingToSocket());
  }
}
void PresentOnlinePlayer::sendMove(int row, int col, Printer& printer) const {
	int n = write(channel_.getClientSocket(), &row, sizeof(row));
	if (n == -1) {
		printer.printMessage(errorWritingToSocket());
	}

	char op = ',';
	n = write(channel_.getClientSocket(), &op, sizeof(op));
	if (n == -1) {
		printer.printMessage(errorWritingToSocket());
	}

	n = write(channel_.getClientSocket(), &col, sizeof(col));
	if (n == -1) {
		printer.printMessage(errorWritingToSocket());
	}
}


void PresentOnlinePlayer::endGame(Printer& printer) {
	cout << "Closing client socket" << endl;//**************************************************************
	sendStatus(END, printer);
	close(channel_.getClientSocket());
}
