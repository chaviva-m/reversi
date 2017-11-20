/*
 * ConsoleNarrator.h
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
 */

#ifndef CONSOLENARRATOR_H_
#define CONSOLENARRATOR_H_

#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "Board.h"
#include "Cell.h"
#include "color.h"
#include "Narrator.h"
#include "Point.h"

/**
 * game narrator which prints output to the console
 */
class ConsoleNarrator: public Narrator {
public:
  ConsoleNarrator();
  virtual const std::string getPlayerName(Color color);
  virtual void printBoard(const Board& board);
  virtual void startTurn(const std::string& player);
  virtual const Point getMove(const std::vector<Cell*>& moves);
  virtual void noPossibleMoves();
  virtual void invalidInput();
  virtual void declareWinner(const std:: string& winner);
  virtual void declareTie();
  virtual ~ConsoleNarrator();
};

#endif /* CONSOLENARRATOR_H_ */
