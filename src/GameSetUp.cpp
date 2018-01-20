/*
 * GameSetUp.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include "GameSetUp.h"
using namespace std;
using namespace message;

GameSetUp::GameSetUp(int board_rows, int board_cols) {
  this->board_ = new Board(board_rows, board_cols);
  this->logic_ = this->standardLogic();
  this->printer_ = this->consoleInterface();
  this->channel_ = NULL;
}
void GameSetUp::setPlayers() {
	this->setPlayersMenu();
}

void GameSetUp::setPlayersMenu() {
	int input;
	string str_input;
	bool valid = false;
	do {
		str_input = "";
		while (str_input.empty()) {
	    this->printer_->printMessage(openingMenu());
		  getline(cin, str_input);
		}
		input = convertStrToPoint(str_input);
		switch(input) {
			case(CONSOLE_RIVAL):
        valid = true;
			  this->players_ = this->consolePlayers();
			  break;
			case(AI_RIVAL):
        valid = true;
		    this->players_ = this->AIAndConsolePlayers();
			  break;
			case(ONLINE_RIVAL):
        valid = true;
			  this->players_ = this->onlinePlayers();
			  break;
		  default:
		    this->printer_->printMessage(invalidInput());
			  break;
	    }
	}while (!valid);
}

int GameSetUp::convertStrToPoint(string& input) {
  int asciiGap = 48;
  int num = 0;
  for (unsigned int i = 0; i < input.size(); i++) {
    if (isdigit(input.at(i))) {
      int digit = (int)input[i] - asciiGap;
        num = num*10 + digit;
    }
  }
  return (num);
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
    string name;
    while(name.empty()) {
      this->printer_->printMessage(getPlayerName((Color((i)))));
      getline(cin, name);
    }
    players[Color(i)] = new HumanPlayer(name, Color(i));
  }
  return players;
}

map<Color,Player*> GameSetUp::AIAndConsolePlayers() {
  map<Color,Player*> players;
  int i;
  for (i = BLACK; i < LAST_COLOR-1; i++) {
    string name;
    while (name.empty()) {
      this->printer_->printMessage(getPlayerName((Color((i)))));
      getline(cin, name);
    }
    players[Color(i)] = new HumanPlayer(name, Color(i));
  }
  players[Color(i)] = new AIPlayer("AI", Color(i));
  return players;
}

map<Color, Player*> GameSetUp::onlinePlayers() {
  map<Color,Player*> players;
  OnlineGamePreparer prep = OnlineGamePreparer(*printer_, channel_);
  players = prep.getOnlinePlayers();
  this->channel_ = prep.getChannel();
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
  if (this->channel_ != NULL) {
    delete this->channel_;
  }
}
