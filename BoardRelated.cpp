/*
 *  BoardRelated.cpp
 *
 * Author: djoffe
 * Dana Joffe
 * ID 312129240
 */

#include "BoardRelated.h"

Location::Location(int i, int j): row(i), col(j) {}
const int Location::getRow() const{ return row; }
const int Location::getCol() const{ return col; }
ostream &operator <<(ostream &out, const Location &loc) {
	out << "(" << loc.row << "," << loc.col <<")";
	return out;
}
ostream &operator <<(ostream &out, const set<Location> &moves){
	out << "";
	for(set<Location>::iterator it=moves.begin();it!=moves.end();it++){
		out << *it << " ";
	}
	return out;
}
const string Location::toString() const {
	string st = "(" + intToStr(this->row) + "," + intToStr(this->col) + ")";
	return st;
}
bool Location::operator< (const Location& e) const {
	if (row < e.getRow()) {
		return true;
	} else {
		if (row > e.getRow()) {
			return false;
		} else {
			if (col < e.getCol()) {
				return true;
			} else {
				if (col > e.getCol()) {
					return false;
				} else {
					return false; //equal
				}
			}
		}
	}
}


Square::Square(PlayerEnum val): val(val) {}
void Square::setToWhite() { val = White; }
void Square::setToBlack() { val = Black; }
void Square::setToSpace() { val = None; }
void Square::flip(PlayerEnum player) {
	this->val = player;
}
const bool Square::contains(PlayerEnum c) const { return val == c; }
const bool Square::contains(Square &s) const { return val == s.val; }
bool Square::isEmpty() const { return (val == None); }

ostream &operator <<(ostream &out, const Square &c){
	out << c.val;
	return out;
}

Board::Board(const int r,const int c): rows(r), cols(c) {
	this->board = new Square*[r];
	for (int l = 0; l < r; ++l)
	    board[l] = new Square[c];
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			Square s;
			s.setToSpace();
			this->board[i][j] = s;
		}
	}
	int midR = r/2;
	int midC = c/2;
	this->board[midR -1][midC -1].setToWhite();
	this->board[midR][midC].setToWhite();
	this->board[midR -1][midC].setToBlack();
	this->board[midR][midC -1].setToBlack();

	this->flipListeners = new vector<FlipListener*>;
}

const int Board::getRowSize() const {
	return this->rows;
}
const int Board::getColSize() const {
	return this->cols;
}
Board::~Board() {
	for (int y = 0; y < this->rows; y++) {
			delete [] this->board[y];
	}
	delete this->flipListeners;//SHOULD DELETE EACH LISTENER
	delete [] this->board;
}
void Board::addFlipListener(FlipListener *flipListener) {
	this->flipListeners->push_back(flipListener);
}
void Board::informFlipListeners(const PlayerEnum from, const PlayerEnum to) const {
	for (unsigned int i = 0; i < this->flipListeners->size(); i++) {
		this->flipListeners->at(i)->flipOccured(from, to);
	}

}
void Board::informFlipListeners(Square& from, const PlayerEnum to) const {
	PlayerEnum color = None;
	if (from.contains(White)) {
		color = White;
	} else if (from.contains(Black)) {
		color = Black;
	}
	this->informFlipListeners(color, to);
}

ostream &operator <<(ostream &out, const Board &b){
	out << " |";
	    for (int k = 0; k < b.cols; k++) {
	    	out << " " << k + 1 << " |";
	    }

	    out << endl << "--";
	    for (int h = 0; h < b.cols; h++) {
	    	out << "----";
	    }
	    out << endl;

	    int j;
	    for (int i = 0; i < b.rows; i++) {
	    	out << i + 1 << "| ";
			for (j = 0; j < b.cols; j++) {
				out << b.board[i][j];
				out << " | ";

			}

			out << endl << "--";
			    for (int d = 0; d < b.cols; d++) {
			    	out << "----";
			    }
			    out << endl;
	    }
	    return out;
}

const Square* Board::in(int r, int c) const {
	return &this->board[r][c];
}

void Board::flip(Location& location, PlayerEnum player) {
	this->flip(location.getRow()-1, location.getCol()-1, player);
}



void Board::flip(int plR, int plC, PlayerEnum player) {
	this->informFlipListeners(board[plR][plC], player);
	this->board[plR][plC].flip(player);//insert

	for (int i = plR - 1; i < plR + 2; i++) {
        for (int j = plC - 1; j < plC + 2; j++) {
            //if (i,j) in range of board
            if (i < this->rows && i >= 0 && j >= 0 and j < this->cols) {
                if (!(this->board[i][j].contains(player)) && !(this->board[i][j].isEmpty())) {
                	//found rival's cell
                	if (i == plR) {//rival is in the same row
                		this->flipInRow(j - plC, j, i, player);
                	} else if (j == plC) { ////rival is in the same column
                		this->flipInCol(i - plR, i, j, player);
                	} else {
                		this->flipInDiagonal(i- plR, j- plC, i, j, player); ////rival is diagonal
                	}
                }
	        }
        }
	 }
}
bool Board::flipInRow(int step, int rivalCol, int row, PlayerEnum player) {
	if (rivalCol < 0 || rivalCol == this->cols) {
		return false;
	} else if (this->board[row][rivalCol].isEmpty()) {
		return false;
	} else if(this->board[row][rivalCol].contains(player)) { //i can create a seriese!
		return true;
	}
	if (this->flipInRow(step, rivalCol + step, row, player)) {
		this->informFlipListeners(board[row][rivalCol], player);
		this->board[row][rivalCol].flip(player);
		return true;
	}
	return false;
}



bool Board::flipInCol(int step, int rivalRow, int col, PlayerEnum player) {
	if (rivalRow < 0 || rivalRow == this->rows) {
			return false;
		} else if (this->board[rivalRow][col].isEmpty()) {
			return false;
		} else if(this->board[rivalRow][col].contains(player)) { //i can create a seriese!
			return true;
		}
		if (this->flipInCol(step, rivalRow + step, col, player)) {
			this->informFlipListeners(board[rivalRow][col], player);
			this->board[rivalRow][col].flip(player);
			return true;
		}
		return false;
}
bool Board::flipInDiagonal(int stepR, int stepC, int rivalRow, int rivalCol, PlayerEnum player) {
	if (rivalRow < 0 || rivalRow == this->rows || rivalCol < 0 || rivalCol == this->cols) {
		return false;
	} else if (this->board[rivalRow][rivalCol].isEmpty()) {
		return false;
	} else if(this->board[rivalRow][rivalCol].contains(player)) { //i can create a seriese!
		return true;
	}
	if (this->flipInDiagonal(stepR, stepC, rivalRow + stepR, rivalCol + stepC, player)) {
		this->informFlipListeners(board[rivalRow][rivalCol], player);
		this->board[rivalRow][rivalCol].flip(player);
		return true;
	}
	return false;

}

