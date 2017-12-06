/*
 * HumanPlayer.h
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include "Board.h"
#include "Player.h"
#include "Printer.h"
#include "messages.h"

#include <limits>
#include <string>
#include <sstream>

/*
 * a Player that interacts via console.
 */
class HumanPlayer: public Player {
public:
   /*
	* constructor.
	* input: name- player's name.
	* 			color - player's representative color.
	*/
	HumanPlayer(const std::string& name, Color color);
   /*
    * asks the player to decide on a move to execute.
    * input: board- current game board
    * 		possibleMoves - move options.
    * 		logic - current game logic (game rules).
    * output: the chosen move in Point representation.
    */
	virtual Point decideOnAMove(Board& board, std::vector<Cell*>& possibleMoves,
	    GameLogic& logic, Printer& printer);
	/*
	 * informs the player that he has no moves to execute.
	 */
	virtual void hasNoMoves(Printer& printer);
	/*
	 * finishes player's turn
	 */
	virtual void endTurn(Point* move, Printer& printer) const;
  /*
   * destructor.
   */
  virtual ~HumanPlayer() {};
};

#endif /* HUMANPLAYER_H_ */
