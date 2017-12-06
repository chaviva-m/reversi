/*
 * GameFlow.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include "GameFlow.h"
using namespace std;
using namespace message;

GameFlow::GameFlow(Board& board, GameLogic& logic,
    const map<Color, Player*>& players, Printer& printer) :
    board_(board), logic_(logic), players_(players), printer_(printer) {
  num_disks_played_ = 0;
}

void GameFlow::playGame() {
  this->initializeBoard();
  printer_.printMessage("\n");
  printer_.printMessage(currentBoard());
  printer_.printBoard(board_);
  //loop through rounds till game over
  bool continue_game = true;
  while (continue_game) {
    continue_game = this->playOneRound();
  }
  this->endGame();
}

void GameFlow::initializeBoard() {
  int b_r = this->board_.getRows();
  int b_c = this->board_.getCols();
  //place 2 disks of each color in center of board
  for (int i = BLACK; i < LAST_COLOR; i++) {
    this->players_[Color(i)]->insertDisk(*this->board_.getCell(b_r/2 - 1,
           b_c/2 - 1 + (1- i)));
    this->num_disks_played_++;
    this->players_[Color(i)]->insertDisk(*this->board_.getCell(b_r/2,
           b_c/2 - (1-i)));
    this->num_disks_played_++;
  }
}

bool GameFlow::playOneRound() {
  for (int c = BLACK; c < LAST_COLOR; c++) {
	Point move;
    //game is over if board is full
    if (num_disks_played_ == (board_.getRows() * board_.getCols())) {
      players_[Color(c)]->endGame(printer_);
      return false;
    }
    vector<Cell*> moves(logic_.getPossibleMoves(board_, Color(c)));
    bool invalid_move = true;
    //player places a disk in one of possible moves
    if (!moves.empty()) {
        while(invalid_move) {
            move = players_[Color(c)]->decideOnAMove(board_, moves,
                                  logic_, printer_);
            printer_.printMessage("\n");
            if (board_.getCell(move) != NULL && find(moves.begin(),
            		moves.end(), board_.getCell(move)) != moves.end()) {
                invalid_move = false;
                players_[Color(c)]->insertDisk(*board_.getCell(move));
                this->num_disks_played_++;
                players_[Color(c)]->flipDisks(logic_.getCellsToFlip(board_,
                		move, Color(c)));
            } else {
                printer_.printMessage(invalidInput());
            }
        }
      } else {
        //printer_.printMessage(noPossibleMoves());
        //if next player has no moves as well, game is over
        if (logic_.getPossibleMoves(board_,
            Color((c + 1) % LAST_COLOR)).empty()) {
          return false;
        //else, play passes on to next player
        } else {
        	players_[Color(c)]->hasNoMoves(printer_);
        }
      }
    printer_.printMessage(currentBoard());
    printer_.printBoard(board_);
    /*if (move.getRow()>-1){
      players_[Color(c)]->endTurn(&move);
    }*/
    if (!moves.empty()) {
      players_[Color(c)]->endTurn(&move, printer_);
    } else {
      players_[Color(c)]->endTurn(NULL, printer_);
    }
  }
  //game continues
  return true;
}

void GameFlow::endGame() {
  Player* winner = this->determineWinner();
  if (winner == NULL) {
    printer_.printMessage(declareTie());
  } else {
    printer_.printMessage(declareWinner(winner->getName()));
  }
}

Player* GameFlow::determineWinner() {
  map<Color, int> num_of_disks = this->logic_.getScores(this->board_);
  //return winner or null if tie
  if (num_of_disks[BLACK] > num_of_disks[WHITE]) {
    return players_[BLACK];
  } else if (num_of_disks[BLACK] < num_of_disks[WHITE]) {
    return players_[WHITE];
  } else {
    return NULL;
  }
}
