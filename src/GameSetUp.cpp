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
	string str_input;
	bool valid = false;
	do {
		this->printer_->printMessage(openingMenu());
		getline(cin, str_input);
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
			case(REMOTE_RIVAL):
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
  map<Color,Player*> players;
  OnlineGamePreparer* prep = NULL;
  prep = new OnlineGamePreparer(*printer_, channel_);
  players = prep->getOnlinePlayers();
  delete prep;
  return players;
}
//void GameSetUp::remotePlayerMenu() {
//  //menu of game options
//  string command_input;
//  stringstream sstream;
//  string command_type;
//  bool valid_input = false;
//  bool started_game = false;
//  while(!started_game || !valid_input) {
//    this->printer_->printMessage(onlineGameMenu());
//    getline(cin, command_input);
//    sstream << command_input;
//    sstream >> command_type;
//    if (strcmp(command_type.c_str(),"start") == 0 ||
//        strcmp(command_type.c_str(),"join") == 0) {
//      valid_input = true;
//      started_game = this->startOnlineGame(command_input);
//    } else if (strcmp(command_type.c_str(),"list_games") == 0) {
//      valid_input = true;
//      this->listAvailableOnlineGames(command_input);
//    } else {
//      printer_->printMessage(invalidInput());
//    }
//  }
//}

//void GameSetUp::sendCommandToServer(string command_msg) {
//  int length = strlen(command_msg.c_str());
//  int n = write(channel_->getClientSocket(), &length, sizeof(length));
//  if (n == -1) {
//    throw(errorWritingToSocket());
//  }
//  n = write(channel_->getClientSocket(), command_msg.c_str(), length);
//  if (n == -1) {
//    throw(errorWritingToSocket());
//  }
//}

//bool GameSetUp::startOnlineGame(string command_msg) {
//  //connect to server
//  try {
//    this->channel_ = this->openCommunicationChannel();
//    this->channel_->connectToServer(*printer_);
//  } catch (const char *msg) {
//    throw(msg);
//  }
//  //send start command to server
//  int result;
//  this->sendCommandToServer(command_msg);
//  int n = read(channel_->getClientSocket(), &result, sizeof(result));
//  if (n == -1) {
//    throw(errorReadingFromSocket());
//  }
//  if (result == -1) {
//    return false;
//  } else {
////    cout << "will now make online player" << endl;
////    this->players_ = this->onlinePlayers();
//    return true;
//  }
//}

//void GameSetUp::listAvailableOnlineGames(string command_msg) {
//  //connect to server
//  try {
//    this->channel_ = this->openCommunicationChannel();
//    this->channel_->connectToServer(*printer_);
//  } catch (const char *msg) {
//    throw(msg);
//  }
//  this->sendCommandToServer(command_msg);
//  //get length of str input
//  int length;
//    int n = read(channel_->getClientSocket(), &length, sizeof(length));
//    if (n == -1) {
//      throw(errorReadingFromSocket());
//    }
//  //get str input of list of games
//  string str;
//  char letter;
//  while (length >0) {
//    n = read(channel_->getClientSocket(), &letter, sizeof(letter));
//    if (n == -1) {
//      throw(errorReadingFromSocket());
//    }
//    str.append(1,letter);
//    length -= 1;
//  }
//  //print list of games
//  this->printer_->printMessage(str);
//}

//map<Color, Player*> GameSetUp::onlinePlayers() {
//  this->remotePlayerMenu();
//  cout << "got back to online players()" << endl;
//  //get name
//  map<Color,Player*> players;
//  this->printer_->printMessage(getPlayerName(LAST_COLOR));
//  string name;
//  getline(cin, name);
//  printer_->printMessage(waitingForAnotherPlayer());
//  //get color from server
//  int color;
//  int n = read(channel_->getClientSocket(), &color, sizeof(color));
//  if (n == -1) {
//    throw(errorReadingFromSocket());
//  }
//  //create players
//  printer_->printMessage(declareColor(Color(color-1)));
//  players[Color(color-1)] = new LocalOnlinePlayer
//        (name, Color(color-1), *channel_);
//  stringstream second_color;
//  second_color << Color(color % LAST_COLOR);
//  players[Color(color % LAST_COLOR)] = new RemoteOnlinePlayer
//      (second_color.str(), Color(color % LAST_COLOR), *channel_);
//  return players;
//}

//CommunicationChannel* GameSetUp::openCommunicationChannel() {
//  //get server IP and port from file
//  ifstream server_info;
//  server_info.open("server_info.txt");
//  if(!server_info.is_open()) {
//    throw(errorOpeningFile());
//  }
//  string server_IP;
//  getline(server_info, server_IP);
//  int port_num;
//  server_info >> port_num;
//  server_info.close();
//  CommunicationChannel* channel = new CommunicationChannel(server_IP, port_num);
//  return channel;
//}

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
