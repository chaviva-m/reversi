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
  this->setPlayersMenu();
}

void GameSetUp::setPlayersMenu() {
	int input;
	string strInput;
	bool valid = false;
	do {
		this->printer_->printMessage(openingMenu());
		getline(cin, strInput);
		input = convertStrToPoint(strInput);
		switch(input) {
			case(CONSOLE_RIVAL):
			  this->players_ = this->consolePlayers();
			  valid = true;
			  break;
			case(AI_RIVAL):
		    this->players_ = this->AIAndConsolePlayers();
			  valid = true;
			  break;
			case(REMOTE_RIVAL):
			  this->players_ = this->onlinePlayers();
			  valid = true;
			  break;
		  default:
			  this->printer_->printMessage(invalidInput());
			  break;
	    }

	}while (!valid) ;
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

map<Color, Player*> GameSetUp::onlinePlayers() {
  //get name
  map<Color,Player*> players;
  this->printer_->printMessage(getPlayerName(LAST_COLOR));
  string name;
  getline(cin, name);
  //connect to server

  this->channel_ = this->openCommunicationChannel();

  if (this->channel_ == NULL) {
    return players;
  }
  this->channel_->connectToServer(*printer_);
  printer_->printMessage(waitingForAnotherPlayer());
  int color;
  int n = read(channel_->getClientSocket(), &color, sizeof(color));
  if (n == -1) {
    printer_->printMessage(errorReadingFromSocket());
    return players;
  }

  //create players
  printer_->printMessage(declareColor(Color(color-1)));
  players[Color(color-1)] = new LocalOnlinePlayer
        (name, Color(color-1), *channel_);
  stringstream second_color;
  second_color << Color(color % LAST_COLOR);
  players[Color(color % LAST_COLOR)] = new RemoteOnlinePlayer
      (second_color.str(), Color(color % LAST_COLOR), *channel_);
  return players;
}

CommunicationChannel* GameSetUp::openCommunicationChannel() {
  //get server IP and port from file
  ifstream server_info;
  server_info.open("server_info.txt");
  if(!server_info.is_open()) {
    printer_->printMessage(errorOpeningFile());
    return NULL;
  }
  const int SIZE = 50;
  string server_IP;
  getline(server_info, server_IP);
  int port_num;
  server_info >> port_num;
  server_info.close();
  CommunicationChannel* channel = new CommunicationChannel(server_IP, port_num);
  return channel;
}

void GameSetUp::playGame() const {
  if (this->players_.empty()) {
    printer_->printMessage(errorInitializingPlayers());
    return;
  }
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
