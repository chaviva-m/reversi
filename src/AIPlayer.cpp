/*
 * AIPlayer.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: djoffe
 */

#include "AIPlayer.h"
using namespace std;

AIPlayer::AIPlayer(const string& name, Color color) :
    Player(name, color) {
}

Point AIPlayer::convertStrToPoint(string& input) {
  int r = 0, c = 0;
  int er = 0, ec = 0;
  bool startOneNum = false;
  bool finishOneNum = false;
  for (unsigned int i = 0; i < input.size(); i++) {
    if (isdigit(input.at(i))) {
      int k = (int)input[i] - 48;
      if (!finishOneNum) {
        startOneNum = true;
        r = r*(10^er) + k;
      } else {
        c = c*(10^ec) + k;
      }
    } else if (startOneNum) {
      finishOneNum = true;
    }
  }
  return (Point(r-1,c-1));
}

Point AIPlayer::decideOnAMove(Board& board, std::vector<Cell*>& possibleMoves,
    GameLogic& logic) {

//	Board copyBoard(board);
//
//	Point p = possibleMoves[0]->getLocation();
//
//	cout << "copy: " << endl;
//	cout << copyBoard;
//	cout << "insert "<< p << endl;
//
//	this->insertDisk(*copyBoard.getCell(p));
//	cout << copyBoard;
//
//	cout << "flip: " << endl;
//	this->flipDisks(logic.getCellsToFlip(copyBoard, p, this->color_));//insertDisk(*copyBoard.getCell(0, 0));
//	cout << copyBoard;
//
//
//	cout << board.getCols() << ", " << board.getRows() << endl;
//	cout << "board: " << endl;
//	cout << board;
//
//	copyBoard = board;
//	cout << "copy reset: " << endl;
//	cout << copyBoard;
//
//	cout << "try:" << endl ;
//	Board copy(4,4);
//	copy = board;
//	cout << copy;


	Point AImove;
	int minRivalScoring = board.getRows() * board.getRows();
	Cell* AIfinalMove;
	// build the result board for each location.
	for(vector<Cell*>::iterator it=possibleMoves.begin();it!=possibleMoves.end();it++){
		Board boardAfterAIMove = board;
		AImove = (*it)->getLocation();
		this->insertDisk(*boardAfterAIMove.getCell(AImove));
		this->flipDisks(logic.getCellsToFlip(boardAfterAIMove, AImove, this->color_));

		Color rivalColor = Color(1-this->color_);
		std::vector<Cell*> rivalsMoveOptions = logic.getPossibleMoves(boardAfterAIMove,
				rivalColor);
		Point rivalMove;
		int maxScoring = -1;
		for(vector<Cell*>::iterator iter=rivalsMoveOptions.begin();
				iter!=rivalsMoveOptions.end();iter++) {
			Board boardAfterRivalMove = boardAfterAIMove;
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
