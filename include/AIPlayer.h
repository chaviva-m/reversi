/*
 * AIPlayer.h
 *
 *  Created on: Nov 24, 2017
 *      Author: djoffe
 */

#ifndef AIPLAYER_H_
#define AIPLAYER_H_

#include "Board.h"
#include "Player.h"
#include <limits>
#include <string>
#include <sstream>

class AIPlayer: public Player {
public:
	AIPlayer(const std::string& name, Color color);
    virtual Point decideOnAMove(Board& board,
      std::vector<Cell*>& possibleMoves, GameLogic& logic);
    virtual ~AIPlayer() {};
private:
	Point convertStrToPoint(std::string& input);
};


#endif /* AIPLAYER_H_ */
