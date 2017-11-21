/*
 * HumanPlayer.h
 *
 *  Created on: Nov 20, 2017
 *      Author: chaviva
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include "Board.h"
#include "Player.h"
#include <limits>
#include <string>
#include <sstream>

class HumanPlayer: public Player {
public:
	HumanPlayer(const std::string& name, Color color);
	std::string getName() const;
  Color getColor() const;
  void insertDisk(Cell& cell) const;
  void flipDisks(const std::vector<Cell*>& cells_to_flip) const;
  virtual Point decideOnAMove(Board& board,
      std::vector<Cell*>& possibleMoves, GameLogic& logic);
	virtual ~HumanPlayer() {};

private:
	Point convertStrToPoint(std::string& input);
};

#endif /* HUMANPLAYER_H_ */
