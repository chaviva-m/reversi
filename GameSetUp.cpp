/*
 * GameSetUp.cpp
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
 */

#include "GameSetUp.h"
using namespace std;

GameSetUp::GameSetUp(int board_rows, int board_cols) {
  this->board_ = new Board(board_rows, board_cols);
  this->logic_ = this->standardLogic();
  this->narrator_ = this->consoleInterface();
  for (int i = BLACK; i < LAST_COLOR; i++) {
    string name = this->narrator_->getPlayerName(Color(i));
    this->players_[Color(i)] = new Player(name, Color(i));
  }
}

GameLogic* GameSetUp::standardLogic() {
  return new StandardGameLogic();
}

Narrator* GameSetUp::consoleInterface() {
  return new ConsoleNarrator();
}

void GameSetUp::playGame() const {
  GameFlow game = GameFlow(*board_, *logic_, players_, *narrator_);
  game.playGame();
}

GameSetUp::~GameSetUp() {
  delete this->board_;
  delete this->logic_;
  delete this->narrator_;
  for (int j = BLACK; j < LAST_COLOR; j++) {
    delete this->players_[Color(j)];
  }
  this->players_.clear();
}
