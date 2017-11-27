/*
 * HumanPlayer.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include "HumanPlayer.h"
using namespace std;

HumanPlayer::HumanPlayer(const string& name, Color color) :
    Player(name, color) {
}

void HumanPlayer::hasNoMoves() const {
	string any_key;
	getline(cin, any_key);
	return;
}

Point HumanPlayer::convertStrToPoint(string& input) {
  int r = 0, c = 0;
  bool startOneNum = false;
  bool finishOneNum = false;
  for (unsigned int i = 0; i < input.size(); i++) {
    if (isdigit(input.at(i))) {
      int k = (int)input[i] - 48;
      if (!finishOneNum) {
        startOneNum = true;
        r = r*10 + k;
      } else {
        c = c*10 + k;
      }
    } else if (startOneNum) {
      finishOneNum = true;
    }
  }
  return (Point(r-1,c-1));
}

Point HumanPlayer::decideOnAMove(Board& board, std::vector<Cell*>& possibleMoves,
    GameLogic& logic) throw(){
  if (possibleMoves.empty()) {
	  throw logic_error("Called to HumanPlayer::decideOnAMove with no possible moves");
  }
  string point;
  getline(cin, point);
  Point move = this->convertStrToPoint(point);
  return move;
}
