/*
 * Player.h
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <string>
#include "Cell.h"
#include "color.h"
#include "GameLogic.h"
#include "Printer.h"
/**
 * player in game, has name and color
 */
class Player {
public:
  /**
   * constructs player.
   * input: std::string name, Color color
   * output: void
   */
  Player(const std::string& name, Color color);
  /**
   * access player's name
   * input: void
   * output: std::string name
   */
  std::string getName() const;
  /**
   * access player's color
   * input: void
   * output: Color color
   */
  Color getColor() const;
  /**
   * insert disk with player's color in cell
   * input: Cell* cell
   * output: void
   */
  void insertDisk(Cell& cell) const;
  /**
   * flip disks in given cells
   * input: std::vector<Cell*> cells_to_flip
   * output: void
   */
  void flipDisks(const std::vector<Cell*>& cells_to_flip) const;
  /*
   * asks the player to decide on a move to execute.
   * input: board- current game board
   * 		possibleMoves - move options.
   * 		logic - current game logic (game rules).
   * output: the chosen move in Point representation.
   */
  virtual Point decideOnAMove(Board& board, std::vector<Cell*>& possibleMoves,
      GameLogic& logic, Printer& printer) = 0;
  /*
   * informs the player that he has no moves to execute.
   */
  virtual void hasNoMoves(Printer& printer) =0;
  /*
   * finishes player's turn
   */
  virtual void endTurn(Point* move, Printer& printer) const = 0;
  /*
   * end of game.
   */
  virtual void endGame(Printer& printer) {};
  /*
   * destructor.
   */
  virtual ~Player() {};

protected:
  std::string name_;
  Color color_;
  /*
  * input: a string that should contain two separated numbers.
  * return: a Location object. Where the player want's to put his color.
  *   if a number is missing- zero is being put instead.
  */
  Point convertStrToPoint(std::string& input);
};

#endif /* PLAYER_H_ */
