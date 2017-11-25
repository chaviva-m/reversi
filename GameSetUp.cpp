/*
 * GameSetUp.cpp
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
 */

#include "GameSetUp.h"
using namespace std;
using namespace message;

GameSetUp::GameSetUp(int board_rows, int board_cols) {
  this->board_ = new Board(board_rows, board_cols);
  this->logic_ = this->standardLogic();
  this->printer_ = this->consoleInterface();
  this->players_ = this->AIAndConsolePlayers();

}

GameLogic* GameSetUp::standardLogic() {
  return new StandardGameLogic();
}

Printer* GameSetUp::consoleInterface() {
  return new ConsolePrinter();
}

map<Color,Player*> GameSetUp::consolePlayers() {
  map<Color,Player*> players;
  for (int i = BLACK; i < LAST_COLOR; i++) {
    this->printer_->printMessage(getPlayerName((Color((i)))));
    string name;
    getline(cin, name);
    players[Color(i)] = new HumanPlayer(name, Color(i));
  }
  return players;
}
map<Color,Player*> GameSetUp::AIAndConsolePlayers() {
  map<Color,Player*> players;
  int i;
  for (i = BLACK; i < LAST_COLOR-1; i++) {
    this->printer_->printMessage(getPlayerName((Color((i)))));
    string name;
    getline(cin, name);
    players[Color(i)] = new HumanPlayer(name, Color(i));
  }
  players[Color(i)] = new AIPlayer("AI", Color(i));
  return players;


}




void GameSetUp::playGame() const {
  GameFlow game = GameFlow(*board_, *logic_, players_, *printer_);
  game.playGame();
}

GameSetUp::~GameSetUp() {
  delete this->board_;
  delete this->logic_;
  delete this->printer_;
  for (int j = BLACK; j < LAST_COLOR; j++) {
    delete this->players_[Color(j)];
  }
  this->players_.clear();
}
