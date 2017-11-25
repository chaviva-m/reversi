/*
 * messages.cpp
 *
 *  Created on: Nov 20, 2017
 *      Author: chaviva
 */

#include "messages.h"

namespace message {

  const string getPlayerName(Color color) {
    stringstream msg;
    msg << "Player " << color << " please enter your name: ";
    return msg.str();
  }

  const string currentBoard() {
    stringstream msg;
    msg << "Current board:" << endl;
    return msg.str();
  }

  const string startTurn(const string& player) {
    stringstream msg;
    msg << player << ": It's your turn." << endl;
    return msg.str();
  }

  const string startTurn(const Color c) {
      stringstream msg;
      msg << c << ": It's your turn." << endl;
      return msg.str();
    }

  const string finishTurn(const string& player, const Point p) {
    stringstream msg;
    msg << player << " played " << p << '\n'<< endl;
    return msg.str();
  }

  const string finishTurn(const Color c, const Point p) {
	stringstream msg;
	msg << c << " played " << p << '\n'<< endl;
	return msg.str();

  }


  const string possibleMoves(const vector<Cell*>& moves) {
    stringstream msg;
    msg << "Your possible moves: ";
    msg << moves[0]->getLocation();
    for (unsigned i = 1; i < moves.size(); i++) {
      msg << "," << moves[i]->getLocation();
    }
    msg << endl;
    msg << "Please enter your move as follows: row column ";
    return msg.str();
  }

  const string noPossibleMoves() {
    stringstream msg;
    msg << "No possible moves." << endl;
    msg << "Play passes back to the other player." << endl;
    msg << "Press any key and then Enter to continue" << endl;
    return msg.str();
  }

  const string invalidInput() {
    stringstream msg;
    msg << "invalid input" << endl;
    return msg.str();
  }

  const string declareWinner(const string& winner) {
    stringstream msg;
    msg << "Game over. The winner is... " << winner << "!" << endl;
    return msg.str();
  }

  const string declareTie() {
    stringstream msg;
    msg << "Game over. It's a tie!" << endl;
    return msg.str();
  }
}
