/*
 * AIPlayer.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include "AIPlayer.h"
using namespace std;
using namespace message;

AIPlayer::AIPlayer(const string& name, Color color) :
    Player(name, color) {
}

void AIPlayer::hasNoMoves(Printer& printer) {
	return;
}

Point AIPlayer::decideOnAMove(Board& board, std::vector<Cell*>& possibleMoves,
    GameLogic& logic, Printer& printer) {
	Point AImove;
	int minRivalScoring = board.getRows() * board.getCols();
	Cell* AIfinalMove;
	Board boardAfterAIMove(board.getRows(), board.getCols());
	// build the result board for each location.
	for(vector<Cell*>::iterator it=possibleMoves.begin();it!=possibleMoves.end();it++){
		boardAfterAIMove = board;
		AImove = (*it)->getLocation();
		this->insertDisk(*boardAfterAIMove.getCell(AImove));
		this->flipDisks(logic.getCellsToFlip(boardAfterAIMove, AImove, this->color_));

		Color rivalColor = Color(1-this->color_);
		std::vector<Cell*> rivalsMoveOptions = logic.getPossibleMoves(boardAfterAIMove,
				rivalColor);
		// if rival won't have moves
		if (rivalsMoveOptions.empty()) {
			return AImove;
		}
		Board boardAfterRivalMove(board.getRows(), board.getCols());
		Point rivalMove;
		// calculate rival's moves and score according to AImove.
		double maxScoring = - std::numeric_limits<double>::infinity();
		for(vector<Cell*>::iterator iter=rivalsMoveOptions.begin();
				iter!=rivalsMoveOptions.end();iter++) {
			boardAfterRivalMove = boardAfterAIMove;
			rivalMove = (*iter)->getLocation();
			(boardAfterRivalMove.getCell(rivalMove))->insertDisk(rivalColor);
			this->flipDisks(logic.getCellsToFlip(boardAfterRivalMove, rivalMove, rivalColor));
			//count the disks.
			map<Color, int> scores = logic.getScores(boardAfterRivalMove);
			int AIscore = scores[this->color_];
			int rivalScore = scores[rivalColor];
			int totalScore = rivalScore - AIscore;
			if (totalScore > maxScoring) {
				maxScoring = totalScore;
			}
		}
		if (maxScoring < minRivalScoring) {
			minRivalScoring = maxScoring;
			AIfinalMove = *it;
		}
	}
	return AIfinalMove->getLocation();
}

void AIPlayer::endTurn(Point* move, Printer& printer) const {
  if (move != NULL) {
    printer.printMessage(finishTurn(color_, *move));
  } else {
    printer.printMessage(noPossibleMovesForPlayer(color_));
  }
}
