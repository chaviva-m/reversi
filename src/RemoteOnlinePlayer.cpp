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

Point RemoteOnlinePlayer::decideOnAMove(Board& board,
    std::vector<Cell*>& possibleMoves, GameLogic& logic, Printer& printer) {
  printer.printMessage(waitingForMove());
  const int SIZE = 6;
  char point[SIZE];
  int n = read(channel_.getClientSocket(), point, SIZE);
  if (n == -1) {
    printer.printMessage(errorReadingFromSocket());
    return Point(-1,-1); //change?
  }
  string point_str = point;
  Point move = this->convertStrToPoint(point_str);
  return move;
}

void RemoteOnlinePlayer::hasNoMoves(Printer& printer) {
  const int SIZE = 7;
  char noMove[SIZE];
  int n = read(channel_.getClientSocket(), noMove, SIZE);
  if (n == -1) {
    printer.printMessage(errorReadingFromSocket());
    return;
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
  const int SIZE = 4;
  char* end_game = "End";
  int n = write(channel_.getClientSocket(), end_game, SIZE);
  if (n == -1) {
    printer.printMessage(errorWritingToSocket());
    return;
  }
}
