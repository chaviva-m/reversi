/*
 * HumanPlayer.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include "HumanPlayer.h"
using namespace std;
using namespace message;

HumanPlayer::HumanPlayer(const string& name, Color color) :
    Player(name, color) {
}

void HumanPlayer::hasNoMoves(Printer& printer) {
  printer.printMessage(startTurn(color_));
  printer.printMessage(noPossibleMovesForPlayer(this->color_));
  printer.printMessage(pressAnyKeyToContinue());
	string any_key;
	getline(cin, any_key);
	return;
}

void HumanPlayer::endTurn(Point* move, Printer& printer) const {
  return;
}

Point HumanPlayer::decideOnAMove(Board& board, vector<Cell*>& moves,
    GameLogic& logic, Printer& printer) {
  printer.printMessage(startTurn(color_));
  printer.printMessage(possibleMoves(moves));
  string point;
  getline(cin, point);
  Point move = this->convertStrToPoint(point);
  return move;
}
