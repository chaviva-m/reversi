/*
 * messages.h
 *
 *  Created on: Nov 20, 2017
 *      Author: chaviva
 */

#ifndef MESSAGES_H_
#define MESSAGES_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Board.h"
#include "Cell.h"
#include "color.h"
#include "Point.h"

using namespace std;

namespace message {

  const string getPlayerName(Color color);

  const string currentBoard();

  const string startTurn(const string& player);

  const string possibleMoves(const vector<Cell*>& moves);

  const string noPossibleMoves();

  const string invalidInput();

  const string declareWinner(const string& winner);

  const string declareTie();
}

#endif /* MESSAGES_H_ */
