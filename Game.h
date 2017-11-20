/*
 * Game.h
 *
 * Author: djoffe
 * Dana Joffe
 * ID 312129240
 */

#ifndef GAME_H_
#define GAME_H_

#include "Printers.h"
#include "Players.h"
#include "Logics.h"

/*
 * in charge of interaction with the players.
 */
class GameManager {
public:
	/*
	 * constructor.
	 * @param log: game logic.
	 * @param board: Reversi board.
	 */
	GameManager(Board& board, GameLogic& log);
	/*
	 * show move options, accepts the player move decision,executes it.
	 * @param player: a Player.
	 * @param printer: a Printer/
	 */
	void makeAMove(Player* player, Printer& printer);
private:
	Board& board;
	GameLogic& logic;
};

/*
 * Reversi game builder.
 */
class Game {
public:
	/*
	 *constructor.
	 *@param r: number or rows.
	 *@param c: number or columns.
	 *@param logic: a game logic.
	 *@param printer: a printer.
	 *@param player1, player2: players for the game.
	 */
	Game(int r = 8, int c = 8,
			GameLogic* logic = new BasicReversiLogic(),
			Printer* printer = new ConsolePrinter(),
			Player* player1 = NULL, Player* player2 = NULL);
	/*
	 * copy constructor.
	 */
	Game(const Game &oldGame);
	/*
	 * destructor.
	 */
	~Game();
	/*
	 * @param p1: player.
	 * @param p2: player.
	 */
	void addPlayers(Player* p1, Player* p2);
	/*
	 * starts the game and ends it.
	 */
	void start();
	/*
	 * calculate who is the winner.
	 */
	void announceWinner() const;
private:
	GameManager *gameManager;
	Board *board;
	GameLogic *logic;
	Player* p1;
	Player* p2;
	FlipCounter* p1Counter;
	FlipCounter* p2Counter;
	Printer* printer;
};


#endif /* GAME_H_ */
