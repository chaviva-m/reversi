/*
 * GameFlow.cpp
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
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
           b_c/2 - 1 + i));
    this->num_disks_played_++;
    this->players_[Color(i)]->insertDisk(*this->board_.getCell(b_r/2,
           b_c/2 - i));
    this->num_disks_played_++;
  }
}

bool GameFlow::playOneRound() {
  for (int c = BLACK; c < LAST_COLOR; c++) {
    printer_.printMessage(currentBoard());
    printer_.printBoard(board_);
    //game is over if board is full
    if (num_disks_played_ == (board_.getRows() * board_.getCols())) {
      return false;
    }
    printer_.printMessage(startTurn(players_[Color(c)]->getName()));
    vector<Cell*> moves(logic_.getPossibleMoves(board_, Color(c)));
    bool invalid_move = true;
      //player places a disk in one of possible moves
      if (!moves.empty()) {
          while(invalid_move) {
            printer_.printMessage(possibleMoves(moves));
            Point move = players_[Color(c)]->decideOnAMove(board_, moves, logic_);
          if (board_.getCell(move.getRow(), move.getCol()) != NULL
              && find(moves.begin(), moves.end(),
              board_.getCell(move.getRow(), move.getCol())) != moves.end()) {
              invalid_move = false;
              players_[Color(c)]->insertDisk(*board_.getCell(move.getRow(),
                           move.getCol()));
              this->num_disks_played_++;
              players_[Color(c)]->flipDisks(logic_.getCellsToFlip(board_,
                  move.getRow(), move.getCol(), Color(c)));
          } else {
            printer_.printMessage(invalidInput());
          }
        }
      //player has no possible moves
      } else {
        printer_.printMessage(noPossibleMoves());
        //if next player has no moves as well, game is over
        if (logic_.getPossibleMoves(board_,
            Color((c + 1) % LAST_COLOR)).empty()) {
          return false;
        //else, play passes on to next player
        } else {
          string any_key; // or char
          getline(cin, any_key); //or cin << any_key
        }
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
  map<Color, int> num_of_disks;
  for (int c = BLACK; c < LAST_COLOR; c++) {
    num_of_disks[Color(c)] = 0;
  }
  //count disks of each color
  for (int i = 0; i < board_.getRows(); i++) {
    for (int j = 0; j < board_.getCols(); j++) {
      if (board_.getCell(i,j)->getDisk() != NULL) {
        for (int c = BLACK; c < LAST_COLOR; c++) {
          if (board_.getCell(i,j)->getDisk()->getColor() == Color(c)) {
            num_of_disks[Color(c)]++;
          }
        }
      }
    }
  }
  //return winner or null if tie
  if (num_of_disks[BLACK] > num_of_disks[WHITE]) {
    return players_[BLACK];
  } else if (num_of_disks[BLACK] < num_of_disks[WHITE]) {
    return players_[WHITE];
  } else {
    return NULL;
  }
}
