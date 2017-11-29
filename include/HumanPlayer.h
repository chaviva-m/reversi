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
	virtual Point decideOnAMove(Board& board,
      std::vector<Cell*>& possibleMoves, GameLogic& logic);
	/*
	 * destructor.
	 */
	virtual ~HumanPlayer() {};
	/*
	 * informs the player that he has no moves to execute.
	 */
	virtual void hasNoMoves() const;

private:
	/*
	* input: a string that should contain two separated numbers.
	* return: a Location object. Where the player want's to put his color.
	* 	if a number is missing- zero is being put instead.
	*/
	Point convertStrToPoint(std::string& input);
};

#endif /* HUMANPLAYER_H_ */
