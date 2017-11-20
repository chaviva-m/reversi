/*
 * Logics.cpp
 *
 * Author: djoffe
 * Dana Joffe
 * ID 312129240
 */

#include "Logics.h"

GameLogic::~GameLogic() {}

BasicReversiLogic::BasicReversiLogic() {}
BasicReversiLogic::~BasicReversiLogic() {}
bool BasicReversiLogic::isMoveValid(const Location loc, const PlayerEnum player, const Board& board) const {
	// check that player put 2 numbers that are different from zero.
	if (loc.getRow() < 1 || loc.getCol() < 1) {
		return false;
	}
	if (loc.getRow() > board.getRowSize() || loc.getCol() > board.getColSize()) {
		return false;
	}

	// check that the move is in possible moves.
	set<Location> moveOptions = this->calculatePossibleMoves(player, board);
	if (moveOptions.find(loc) == moveOptions.end()) {
		return false;
	}
	return true;
}
const set<Location> BasicReversiLogic::getMoveOptions(const PlayerEnum player, const Board& board) const {
	return this->calculatePossibleMoves(player, board);
}
bool BasicReversiLogic::haveMoves(const PlayerEnum player, const Board& board) const {
	return !((this->calculatePossibleMoves(player, board)).empty());
}
BasicReversiLogic::BasicReversiLogic(const BasicReversiLogic &oldHumanLogic) {}
BasicReversiLogic * BasicReversiLogic::clone () const {
	return new BasicReversiLogic(*this);
}


bool BasicReversiLogic::isCellOptional(int plR, int plC, PlayerEnum player, const Board& board) const {
    for (int i = plR - 1; i < plR + 2; i++) {
        for (int j = plC - 1; j < plC + 2; j++) {
            //if (i,j) in range of board
            if (i < board.getRowSize() && i >= 0 && j >= 0 and j < board.getColSize()) {
                if (!(board.in(i, j)->contains(player)) && !(board.in(i, j)->isEmpty())) {
                	//found rival's cell
                	if (i == plR) {//rival is in the same row
                		if (this->isRowMoveLegit(plC, j, i, player, board)) {
                			return true;
                		}
                	} else if (j == plC) { ////rival is in the same column
                		if (this->isColMoveLegit(plR, i, j, player, board)) {
                			return true;
                		}
                	} else if (this->isDiagonalMoveLegit(plR, plC, i, j, player, board)) { ////rival is diagonal
                			return true;
                	}
                }

            }
        }
    }
    return false;;
}


const set<Location> BasicReversiLogic::calculatePossibleMoves(PlayerEnum player, const Board& board) const {
	set<Location> moves;
	int r;
	int c;
	for (r = 0; r < board.getRowSize(); r++) { // go over lines
		for (c = 0; c < board.getColSize(); c++) { // go over columns
			if (board.in(r, c)->isEmpty()) {
				if (this->isCellOptional(r, c, player, board)) {
					moves.insert(Location(r + 1, c + 1));
				}
			}
		}
	}
	return moves;
}


bool BasicReversiLogic::isDiagonalMoveLegit(int empCellRow, int empCellCol,
	int rivalRow, int rivalCol, PlayerEnum player, const Board& board) const {
	int stepC = rivalCol - empCellCol;
	int stepR = rivalRow - empCellRow;
	rivalRow += stepR;
	rivalCol += stepC;

	//i'm not at the end of the board
	while (rivalCol > -1 && rivalCol < board.getColSize() && rivalRow > -1 && rivalRow < board.getRowSize()) {
		// reached an empty cell
		if (board.in(rivalRow, rivalCol)->isEmpty()) {
			return false;
		} else if(board.in(rivalRow, rivalCol)->contains(player)) { //i can create a seriese!
			return true;
		}
		rivalRow += stepR;
		rivalCol += stepC;
	}
	//end of board
	return false;
}

bool BasicReversiLogic::isRowMoveLegit(int empCellCol, int rivalCol, int row, PlayerEnum player, const Board& board) const {
	int step = rivalCol - empCellCol;
	rivalCol += step;
	//i'm not at the end of the board
	while (rivalCol > -1 && rivalCol < board.getColSize()) {
		// reached an empty cell
		if (board.in(row, rivalCol)->isEmpty()) {
			return false;
		} else if(board.in(row, rivalCol)->contains(player)) { //i can create a seriese!
			return true;
		}
		rivalCol += step;
	}
	//end of board
	return false;
}
bool BasicReversiLogic::isColMoveLegit(int empCellRow, int rivalRow, int col, PlayerEnum player, const Board& board) const {
	int step = rivalRow - empCellRow;
	rivalRow += step;
	//i'm not at the end of the board
	while (rivalRow > -1 && rivalRow < board.getRowSize()) {
		// reached an empty cell
		if (board.in(rivalRow, col)->isEmpty()) {
			return false;
		} else if(board.in(rivalRow, col)->contains(player)) { //i can create a seriese!
			return true;
		}
		rivalRow += step;
	}
	//and of board
	return false;

}

