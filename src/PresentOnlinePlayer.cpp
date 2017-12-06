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
  const int SIZE = 7;
  stringstream strng;
  if (move == NULL) {
    strng << "NoMove";
  } else {
    strng << *move;
  }
  const string& temp = strng.str();
  const char* msg = temp.c_str();
  int n = write(channel_.getClientSocket(), msg, SIZE);
  if (n == -1) {
    printer.printMessage(errorWritingToSocket());
    return;
  }
}

void PresentOnlinePlayer::endGame(Printer& printer) {
  const int SIZE = 4;
  char* end_game = "End";
  int n = write(channel_.getClientSocket(), end_game, SIZE);
  if (n == -1) {
    printer.printMessage(errorWritingToSocket());
    return;
  }
}
