/*
 * Player.h
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <string>

#include "Cell.h"
#include "color.h"
#include "GameLogic.h"
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

  virtual Point decideOnAMove(Board& board,
      std::vector<Cell*>& possibleMoves, GameLogic& logic) = 0;

  virtual ~Player() {};

protected:
  std::string name_;
  Color color_;
};

#endif /* PLAYER_H_ */
