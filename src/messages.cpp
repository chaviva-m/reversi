/*
 * messages.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include "messages.h"

namespace message {

  const string openingMenu() {
    stringstream msg;
    msg << "Choose an opponent type:" << endl;
    msg << CONSOLE_RIVAL << ". a human local player" << endl;
    msg << AI_RIVAL << ". an AI player" << endl;
    msg << REMOTE_RIVAL << ". a remote player" << endl;
    msg << NONE << ". exit" << endl;
    return msg.str();
  }

  const string onlineGameMenu() {
    stringstream msg;
    msg << "Choose a game to play." << endl;
    msg << "1. To start a new game: enter 'start <name>' (example: start myGame)" << endl;
    msg << "2. To see the list of existing available games to join: enter 'list_games'" << endl;
    msg << "3. To join an existing game: enter 'join <name>' (example:join myGame)" << endl;
    return msg.str();
  }

  const string errorOpeningFile() {
    stringstream msg;
    msg << "Cannot open file with server information." << endl;
    return msg.str();
  }

  const string connectedToServer() {
    stringstream msg;
    msg << "Connected to server" << endl;
    return msg.str();
  }

  const string waitingForAnotherPlayer() {
    stringstream msg;
    msg << "Waiting for another player to join..." << endl;
    return msg.str();
  }

  const string errorReadingFromSocket() {
    stringstream msg;
    msg << "Error reading from socket." << endl;
    return msg.str();
  }

  const string errorWritingToSocket() {
    stringstream msg;
    msg << "Error writing to socket" << endl;
    return msg.str();
  }

  const string getPlayerName(Color color) {
    stringstream msg;
    if(color == LAST_COLOR) {
    	msg << "Please enter your name: ";
    } else {
    	msg << "Player " << color << " please enter your name: ";
    }
    return msg.str();
  }
  const string declareColor(Color color) {
      stringstream msg;
      msg << "Your color is " << color;
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

  const string noPossibleMovesForPlayer(Color color) {
    stringstream msg;
    msg << color << " has no possible moves." << endl;
    return msg.str();
  }

  const string noPossibleMovesOnBoard() {
    stringstream msg;
    msg << "There are no more legal moves on the board for either player." << endl;
    return msg.str();
  }

  const string waitingForMove() {
    stringstream msg;
    msg << "Waiting for other player's move..." << endl;
    return msg.str();
  }

  const string pressAnyKeyToContinue() {
    stringstream msg;
    msg << "Play passes back to the other player." << endl;
    msg << "Press any key and then Enter to continue" << endl;
    return msg.str();
  }

  const string invalidInput() {
    stringstream msg;
    msg << "Input is invalid. Please try again." << endl;
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
