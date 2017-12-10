/*
 * RemoteOnlinePlayer.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
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

  }
  if(status != HAS_MOVE) {

  }
  //Read move arguments
  r = read(channel_.getClientSocket(), &row, sizeof(row));
  if (r == -1) {

  }
  r = read(channel_.getClientSocket(), &sep, sizeof(sep));
  if (r == -1) {

  }
  r = read(channel_.getClientSocket(), &col, sizeof(col));
  if (r == -1) {

  }
  return Point(row, col);

}

void RemoteOnlinePlayer::hasNoMoves(Printer& printer) {
	printer.printMessage(waitingForMove());
	  int status;
	  int r = read(channel_.getClientSocket(), &status, sizeof(status));
	  if (r == -1) {

	  }
	  if(status != NO_MOVES) {

	  }
}

void RemoteOnlinePlayer::endTurn(Point* move, Printer& printer) const {
  if (move != NULL) {
    printer.printMessage(finishTurn(color_, *move));
  } else {
    printer.printMessage(noPossibleMovesForPlayer(color_));
  }
}

void RemoteOnlinePlayer::endGame(Printer& printer) {
	int stat = END;
	int n = write(channel_.getClientSocket(), &stat, sizeof(stat));
    if (n == -1) {
      printer.printMessage(errorWritingToSocket());
	}
}

