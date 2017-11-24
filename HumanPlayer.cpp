/*
 * HumanPlayer.cpp
 *
 *  Created on: Nov 20, 2017
 *      Author: chaviva
 */

#include "HumanPlayer.h"
using namespace std;

HumanPlayer::HumanPlayer(const string& name, Color color) :
    Player(name, color) {
}

Point HumanPlayer::convertStrToPoint(string& input) {
  int r = 0, c = 0;
  int er = 0, ec = 0;
  bool startOneNum = false;
  bool finishOneNum = false;
  for (unsigned int i = 0; i < input.size(); i++) {
    if (isdigit(input.at(i))) {
      int k = (int)input[i] - 48;
      if (!finishOneNum) {
        startOneNum = true;
        r = r*(10^er) + k;
      } else {
        c = c*(10^ec) + k;
      }
    } else if (startOneNum) {
      finishOneNum = true;
    }
  }
  return (Point(r,c));
}

Point HumanPlayer::decideOnAMove(Board& board, std::vector<Cell*>& possibleMoves,
    GameLogic& logic) {
  string point;
  getline(cin, point);
  Point move = this->convertStrToPoint(point);
  return move;
}
