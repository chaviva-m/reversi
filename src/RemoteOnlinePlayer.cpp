/*
 * RemoteOnlinePlayer.cpp
 *
 *  Created on: Dec 6, 2017
 *      Author: chaviva
 */

#include "RemoteOnlinePlayer.h"
using namespace std;
using namespace message;

RemoteOnlinePlayer::RemoteOnlinePlayer(const string& name, Color color,
    CommunicationChannel& channel) : Player(name, color), channel_(channel) {
}

// this method is being called ONLY IF possibleMoves isn't empty.
Point RemoteOnlinePlayer::decideOnAMove(Board& board,
    std::vector<Cell*>& possibleMoves, GameLogic& logic, Printer& printer) {
  printer.printMessage(waitingForMove());
  int row, col, status;
  char sep;
  int r = read(channel_.getClientSocket(), &status, sizeof(status));
  if (r == -1) {
      printer.printMessage(errorReadingFromSocket());
      return Point(-1,-1); //change? ****************************************************************
  }

  if(status != HAS_MOVE) {
 	cout <<"PROBLAME IN: RemoteOnlinePlayer::decideOnAMove. closing socket" << endl;
 	endGame(printer);
  }
  //Read move arguments
  r = read(channel_.getClientSocket(), &row, sizeof(row));
  if (r == -1) {
     printer.printMessage(errorReadingFromSocket());
  }
  r = read(channel_.getClientSocket(), &sep, sizeof(sep));
  if (r == -1) {
     printer.printMessage(errorReadingFromSocket());
  }
  r = read(channel_.getClientSocket(), &col, sizeof(col));
  if (r == -1) {
     printer.printMessage(errorReadingFromSocket());
  }
  return Point(row, col);

}

void RemoteOnlinePlayer::hasNoMoves(Printer& printer) {
	printer.printMessage(waitingForMove());
	  int status;
	  int r = read(channel_.getClientSocket(), &status, sizeof(status));
	  if (r == -1) {
	      printer.printMessage(errorReadingFromSocket());
	      return;
	  }
	  if(status != NO_MOVES) {
	 	cout <<"PROBLAME IN: RemoteOnlinePlayer::hasNoMoves. closing socket" << endl;
	 	endGame(printer);
	  }
}

void RemoteOnlinePlayer::endTurn(Point* move, Printer& printer) const {
  if (move != NULL) {
    printer.printMessage(finishTurn(color_, *move));
  } else {
    printer.printMessage(noPossibleMoves(color_));
  }
}

void RemoteOnlinePlayer::endGame(Printer& printer) {
	int stat = END;
	int n = write(channel_.getClientSocket(), &stat, sizeof(stat));
    if (n == -1) {
		printer.printMessage(errorWritingToSocket());
	    return;
	}
}
