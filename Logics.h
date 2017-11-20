/*
 * Logics.h
 *
 * Author: djoffe
 * Dana Joffe
 * ID 312129240
 */


#ifndef LOGICS_H_
#define LOGICS_H_

#include "BoardRelated.h"

/*
 * pure virtual class.
 * determines the logic rules that a Reversi game is based on.
 */
class GameLogic {
public:
	/*
	 * virtual destructor.
	 */
	virtual ~GameLogic();
	/*
	 * virtual constructor (copying)
	 * @return: an address of a new GameLogic.
	 */
	virtual GameLogic * clone () const = 0;
	/*
	 * @param loc: move location on the board.
	 * @param player: the player type that execute the move.
	 * @param board: the board on which the move is done.
	 * @return: if a move is valid.
	 */
	virtual bool isMoveValid(const Location loc, const PlayerEnum player, const Board& board) const =0;
	/*
	 * @param board: Reversi board..
	 * @param player: player type.
	 * return: a set of possible locations for a player to choose.
	 */
	virtual const set<Location> getMoveOptions(const PlayerEnum player, const Board& board) const =0;
	/*
	 * @param player: the player type that wants to make a move.
	 * @param board: Reversi board.
	 * @return: wether the player have a possible move in a current board position.
	 */
	virtual bool haveMoves(const PlayerEnum player, const Board& board) const =0;
};

class BasicReversiLogic: public GameLogic {
public:
	/*
	 * constructor.
	 */
	BasicReversiLogic();
	/*
	 * Copy constructor
	 */
	BasicReversiLogic(const BasicReversiLogic &oldHumanLogic);
	/*
	 * virtual constructor (copying)
	 * @return: an address of a new BasicReversiLogic.
	 */
	BasicReversiLogic * clone () const;      // Virtual constructor (copying)
	/*
	 * virtual destructor.
	 */
	virtual ~BasicReversiLogic();
	/*
	 * @param loc: move location on the board.
	 * @param player: the player type that execute the move.
	 * @param board: the board on which the move is done.
	 * @return: if a move is valid.
	 */
	virtual bool isMoveValid(const Location loc, const PlayerEnum player, const Board& board) const;
	/*
	 * @param board: Reversi board..
	 * @param player: player type.
	 * return: a set of possible locations for a player to choose.
	 */
	virtual const set<Location> getMoveOptions(const PlayerEnum player, const Board& board) const;
	/*
	 * @param player: the player type that wants to make a move.
	 * @param board: Reversi board.
	 * @return: wether the player have a possible move in a current board position.
	 */
	virtual bool haveMoves(const PlayerEnum player, const Board& board) const;


	/*
	* @return: whether a (r,c) location in board can be flipped to player type.
	 */
	bool isCellOptional(int r, int c, PlayerEnum player, const Board& board) const;
	/*
	 * @param player: a player type.
	 * @return: a set with all the possible move locations for player type player.
	 */
	const set<Location> calculatePossibleMoves(PlayerEnum player, const Board& board) const;

	/*
	 * @param empCellRow: the row player wants to choose.
	 * @param empCellCol: the column player wants to choose.
	 * @param rivalRow: the row in which a rival's square is found.
	 * @param rivalCol: the column in which a rival's square is found.
	 * @param player: player type.
	 * @return: true if flipping the (empCellRow,empCellCol) cell in board
	 * to be player type would cause some more diagonal flipping.
	 */
	bool isDiagonalMoveLegit(int empCellRow, int empCellCol,
			int rivalRow, int rivalCol, PlayerEnum player, const Board& board) const;
	/*
	 * @param row: the row player wants to choose.
	 * @param empCellCol: the column player wants to choose.
	 * @param rivalCol: the column in which a rival's square is found.
	 * @param player: player type.
	 * @return: true if flipping the (row,empCellCol) cell in board
	 * to be player type would cause some more flipping in row.
	 */
	bool isRowMoveLegit(int empCellCol, int rivalCol, int row, PlayerEnum player, const Board& board) const;
	/*
	 * @param col: the column player wants to choose.
	 * @param empCellRow: the row player wants to choose.
	 * @param rivalRow: the row in which a rival's square is found.
	 * @param player: player type.
	 * @return: true if flipping the (row,empCellCol) cell in board
	 * to be player type would cause some more flipping in column.
	 */
	bool isColMoveLegit(int empCellRow, int rivalRow, int col, PlayerEnum player, const Board& board) const;




};

#endif /* LOGICS_H_ */
