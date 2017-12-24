/*
 * messages.h
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#ifndef MESSAGES_H_
#define MESSAGES_H_

#include "Board.h"
#include "Cell.h"
#include "color.h"
#include "onlineOptionEnums.h"
#include "Point.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/*
 * Independent functions that return a string message.
 * All functions that get no parameters return a message with the essence of their name.
 */
namespace message {

  const string openingMenu();

  const string onlineGameMenu();

  const string errorOpeningFile();

  const string connectedToServer();

  const string waitingForAnotherPlayer();

  const string errorReadingFromSocket();

  const string errorWritingToSocket();

  const string declareColor(Color color);
  /*
   * returns a string with the player's name (the player who's
   * color is the input color).
   */
  const string getPlayerName(Color color);

  const string currentBoard();

  /*
   * gets a player's name string representation and returns
   * a sentence that tells its his turn.
   */
  const string startTurn(const string& player);
  /*
   * gets a player's color and returns
   * a sentence that tells its his turn.
   */
  const string startTurn(const Color c);
  /*
   * gets a player's name string representation and his last move,
   * and returns a sentence that declares his move.
   */
  const string finishTurn(const string& player, const Point p);
  /*
   * gets a player's color and his last move,
   * and returns a sentence that declares his move.
   */
  const string finishTurn(const Color c, const Point p);
  /*
  * return string message including the playe's possible moves.
  * input: vector with possible moves.
  */
  const string possibleMoves(const vector<Cell*>& moves);

  const string noPossibleMovesForPlayer(Color color);

  const string noPossibleMovesOnBoard();

  const string waitingForMove();

  const string pressAnyKeyToContinue();

  const string invalidInput();

  const string declareWinner(const string& winner);

  const string declareTie();
}

#endif /* MESSAGES_H_ */
