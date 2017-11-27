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
  this->setPlayers();
}


void GameSetUp::setPlayers() {
	this->printer_->printMessage("for playing against human player: press 1\n"
			"for playing against the computer: press 2\n");
	int input;
	string dummy;
	cin >> input;
	bool valid = false;
	while (!valid) {
	  switch(input) {
	  	case(1):
		   getline(cin, dummy);
	  	   this->players_ = this->consolePlayers();
	  	   valid = true;
	  	   break;
	  	case(2):
     	   getline(cin, dummy);
           this->players_ = this->AIAndConsolePlayers();
	  	   valid = true;
	  	   break;
  		default:
		   this->printer_->printMessage("that was not an option. choose again\n");
	  }
	}
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
