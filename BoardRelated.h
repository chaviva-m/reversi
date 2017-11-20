/*
 * BoardRelated.h
 *
 * Author: djoffe
 * Dana Joffe
 * ID 312129240
 */

#ifndef BOARDRELATED_H_
#define BOARDRELATED_H_

#include "GameAssistants.h"

/*
 * hold a point, x and y. can be on the screen, can
 * be of a cell in a board.
 */
class Location {
public:
	/*
	 * constructor.
	 * @param i: row;
	 * @param r: column;
	 */
	Location(int i, int j);
	/*
	 * @return: the location in a (x,y) formation.
	 */
	const string toString() const;
	/*
	 * @return: row.
	 */
	const int getRow() const;
	/*
	 * @return: column.
	 */
	const int getCol() const;
	/*
	 * overloading print operator.
	 */
	friend ostream &operator <<(ostream &out, const Location &loc);
	/*
	 * overloading compare operator <.
	 */
	bool operator< (const Location& e) const;
private:
	int row;
	int col;
};

/*
 * global print overloading for set<Location> printing.
 */
ostream &operator <<(ostream &out, const set<Location> &moves);

/**
 * represents a solo cell in a Reversi game board.
 */
class Square {
public:
	/**
	 * default constructor.
	 */
	Square(PlayerEnum val = None);
	/**
	 * set the value of the cell to PlayerEnum.White.
	 */
	void setToWhite();
	/**
	 * set the value of the cell to PlayerEnum.Black.
	 */
	void setToBlack();
	/**
	 * set the value of the cell to PlayerEnum.None.
	 */
	void setToSpace();
	/*
	 * @return: if the cell contains PlayerEnum.None.
	 */
	bool isEmpty() const;
	/**
	 * operator overloading:
	 * @return: ostream contains cell's value.
	 */
	friend ostream &operator <<(ostream &out, const Square &c);
	/*
	 * @param c: a player type.
	 * @return: if the cell contains param c.
	 */
	const bool contains(PlayerEnum c) const;
	/*
	 * @param s: a cell in the board.
	 * @return: if the cell contains s's player type..
	 */
	const bool contains(Square &s) const;
	/*
	 * changes the square value to player.
	 * @param player: a player type.
	 */
	void flip(PlayerEnum player);
private:
	PlayerEnum val;

};

/**
 * a Reversi game board.
 */
class Board {
public:
	/**
	 * constructor.
	 * @param r board's row number.
	 * @param c board's columns number.
	 */
	Board(const int r = DROWS,const int c = DCOLS);
	/*
	 * destructor.
	 */
	~Board();
	/**
	 * operator overloading:
	 * @return: ostream contains the board's representation.
	 */
	friend ostream &operator <<(ostream &out, const Board &board);
	/*
	 * @return: how many rows in board.
	 */
	const int getRowSize() const;
	/*
	 * @return: how many columns in board.
	 */
	const int getColSize() const;

	/*
	 * flips to player in the r,c location in board.
	 * @param r: row.
	 * @param c: column.
	 * @param player: player type.
	 */
	void flip(int r, int c, PlayerEnum player);
	/*
	 * flips to player in location in board.
	 * @param location: a location in board.
	 * @param player: player type.
	 */
	void flip(Location& location, PlayerEnum player);
	/*
	 * recursive row-flipping function.
	 * @param step: the direction to go on flipping in row.
	 * @param rivalCol: start flipping location.
	 * @param row: flipping row.
	 * @param player: player type.
	 * @return: true if this is a possible flip row.
	 */
	bool flipInRow(int step, int rivalCol, int row, PlayerEnum player);
	/*
	 * recursive column-flipping function.
	 * @param step: the direction to go on flipping in column.
	 * @param rivalRow: start flipping location.
	 * @param column: flipping column.
	 * @param player: player type.
	 * @return: true if this is a possible flip column.
	 */
	bool flipInCol(int step, int rivalRow, int col, PlayerEnum player);
	/*
	 * recursive diagonal-flipping function.
	 * @param stepR: the direction to go on flipping in rivalRow.
	 * @param stepC: the direction to go on flipping in rivalCol.
	 * @param rivalRow: start flipping row location.
	 * @param rivalCol: start flipping column location.
	 * @param player: player type.
	 * @return: true if this is a possible flip column.
	 */
	bool flipInDiagonal(int stepR, int stepC, int rivalRow, int rivalCol, PlayerEnum player);

	/*
	 * @param flipListener: a FlipListener;
	 */
	void addFlipListener(FlipListener *flipListener);
	/*
	* @param from: the player type that is being flipped.
	* @param to: the player type that is now.
	*/
	void informFlipListeners(const PlayerEnum from, const PlayerEnum to) const;
	/*
	* @param from: the square that is being flipped.
	* @param to: the player type that is now.
	*/
	void informFlipListeners(Square& from, const PlayerEnum to) const;

	/*
	 * getter.
	 * return: the cell in the r row and c column.
	 */
	const Square* in(int r, int c) const;

private:
	// default row the columns number.
	static const int DROWS = 8;
	static const int DCOLS = 8;
	const int rows;
	const int cols;
	Square** board;
	vector<FlipListener*>* flipListeners;
};

#endif /* BOARDRELATED_H_ */
