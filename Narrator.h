/*
 * Narrator.h
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
 */

#ifndef NARRATOR_H_
#define NARRATOR_H_

#include <string>
#include <vector>

#include "Board.h"
#include "Cell.h"
#include "color.h"
#include "Point.h"

/**
 * game narrator.
 * abstract class.
 */
class Narrator {
public:
  Narrator() {};
  /**
   * requests color player's name and returns input
   * input: Color color
   * output: std::string name
   */
  virtual const std::string getPlayerName(Color color) = 0;
  /**
   * prints board to screen
   * input: Board& board
   * output: void
   */
  virtual void printBoard(const Board& board) = 0;
  /**
   * inform player it is his/her turn
   * input: std::string player
   * output: void
   */
  virtual void startTurn(const std::string& player) = 0;
  /**
   * inform player of possible moves, request and return player's choice
   * input: std::vector<Cell*> moves
   * output: Point the move
   */
  virtual const Point getMove(const std::vector<Cell*>& moves) = 0;
  /**
   * inform player he/she has no possible moves
   * input: void
   * output: void
   */
  virtual void noPossibleMoves() = 0;
  /**
   * informs player that his/her input is invalid
   * input: void
   * output: void
   */
  virtual void invalidInput() = 0;
  /**
   * declare winner as winner of game
   * input: std:: string winner
   * output: void
   */
  virtual void declareWinner(const std:: string& winner) = 0;
  /**
   * declare tie
   * input: void
   * output: void
   */
  virtual void declareTie() = 0;
  /**
   * destructs narrator
   * input: void
   * output: void
   */
  virtual ~Narrator() {};
};

#endif /* NARRATOR_H_ */
