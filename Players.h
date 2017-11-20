/*
 * Players.h
 *
 * Author: djoffe
 * Dana Joffe
 * ID 312129240
 */

#ifndef PLAYERS_H_
#define PLAYERS_H_

//#include "SharedCode.h"
#include "BoardRelated.h"

/*
 * virtual class that represents a Reversi player.
 */
class Player {
public:
	/*
	 * virtual destructor.
	 */
	virtual ~Player();
	/*
	 * virtual constructor (copying)
	 * @return: an address of a new player.
	 */
	virtual Player * clone ()= 0;  // Virtual constructor (copying)
	/*
	 * @return: the representation of the player.
	 */
	virtual const PlayerEnum getColor() const =0;

	virtual Location decideOnAmove(Board& board, set<Location>& possibleMoves)=0;//should get game logic

	//flip(....);
	//insert(...);
};

/*
 *
 */
class HumanPlayer: public Player {
public:
	/*
	 * defaultconstructor.
	 */
	HumanPlayer(PlayerEnum color);
	/*
	 * Copy constructor.
	 */
	HumanPlayer(const HumanPlayer &oldHumanPlayer);
	/*
	 * virtual constructor (copying)
	 * @return: an address of a new HumanPlayer.
	 */
	virtual HumanPlayer* clone ();
	/*
	 * virtual destructor.
	 */
	virtual ~HumanPlayer();
	/*
	 * @return: the representation of the HumanPlayer.
	 */
	virtual const PlayerEnum getColor() const;
	/*
	 * @param board: Reversi board.
	 * @param possible moves: all the moves accepted by the curren game logic.
	 * @return: the location the player chose to put his color.
	 */
	virtual Location decideOnAmove(Board& board, set<Location>& possibleMoves);
	/*
	 *@param input: a string that should contain two separated numbers.
	 *@return: a Location object. Where the
	 *	player want's to put his color.
	 */
	virtual Location convertStrToLocation(string& input);
private:
	PlayerEnum color;
};

#endif /* PLAYERS_H_ */
