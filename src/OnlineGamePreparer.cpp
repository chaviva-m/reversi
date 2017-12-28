/*
 * OnlinePlayersCreator.cpp
 *
 *  Created on: Dec 26, 2017
 *      Author: chaviva
 */

#include "OnlineGamePreparer.h"
using namespace std;
using namespace message;

OnlineGamePreparer::OnlineGamePreparer(Printer& printer,
    CommunicationChannel* channel) : printer_(printer), channel_(channel) {
  this->prepareOnlineGame();
}

void OnlineGamePreparer::prepareOnlineGame() {
  this->remotePlayerMenu();
//  this->AlterRemotePlayerMenu();
  //get name
  map<Color,Player*> players;
  this->printer_.printMessage(getPlayerName(LAST_COLOR));
  string name;
  getline(cin, name);
  printer_.printMessage(waitingForAnotherPlayer());
  //get color from server
  int color;
  int n = read(channel_->getClientSocket(), &color, sizeof(color));
  if (n == -1) {
    throw(errorReadingFromSocket());
  }
  //create players
  printer_.printMessage(declareColor(Color(color-1)));
  players[Color(color-1)] = new LocalOnlinePlayer
        (name, Color(color-1), *channel_);
  stringstream second_color;
  second_color << Color(color % LAST_COLOR);
  players[Color(color % LAST_COLOR)] = new RemoteOnlinePlayer
        (second_color.str(), Color(color % LAST_COLOR), *channel_);
  this->players_ = players;
}

std::map<Color,Player*> OnlineGamePreparer::getOnlinePlayers() {
  return this->players_;
}

void OnlineGamePreparer::remotePlayerMenu() {
  //menu of game options
  string command_input;
  stringstream sstream;
  string command_type;
  bool valid_input = false;
  bool started_game = false;

  while(!started_game || !valid_input) {
    this->printer_.printMessage(onlineGameMenu());
    getline(cin, command_input);
    sstream.str(command_input);
    sstream >> command_type;
    sstream.seekg(0, ios::beg);

    if (strcmp(command_type.c_str(),"start") == 0 ||
        strcmp(command_type.c_str(),"join") == 0) {
      valid_input = true;
      started_game = this->startOnlineGame(command_input);

    } else if (strcmp(command_type.c_str(),"list_games") == 0) {
      valid_input = true;
      this->listAvailableOnlineGames(command_input);

    } else {
      printer_.printMessage(invalidInput());
    }
  }
}

int OnlineGamePreparer::convertStrToInt(string& input) {
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

void OnlineGamePreparer::AlterRemotePlayerMenu() {
  //menu of game options
//  string command_input;

  int input;
  string command, gameName;
  bool valid_input = false;
  bool started_game = false;

  do {
    this->printer_.printMessage(AlterOnlineGameMenu());
	getline(cin, command);
	input = convertStrToInt(command);
	switch(input) {
		case(START_GAME):
    	    valid_input = true;
		    this->printer_.printMessage("Enter games' name\n");
		    getline(cin, gameName);
	        started_game = this->startOnlineGame("start", gameName);
		    break;
		case(LIST_GAMES):
		    valid_input = true;
		    this->listAvailableOnlineGames();
		    break;
		case(JOIN_GAME):
    	    valid_input = true;
			this->printer_.printMessage("Enter games' name\n");
			getline(cin, gameName);
			started_game = this->startOnlineGame("join", gameName);
//            started_game = this->startOnlineGame(command, "");
		    break;
		default:
		    printer_.printMessage(invalidInput());
		    break;
	}

  }while(!started_game || !valid_input);
}



void OnlineGamePreparer::listAvailableOnlineGames() {
	string command = "list_games";
	listAvailableOnlineGames(command);
}


void OnlineGamePreparer::listAvailableOnlineGames(string command_msg) {
  //connect to server
  try {
    this->channel_ = this->openCommunicationChannel();
    this->channel_->connectToServer(printer_);
  } catch (const char *msg) {
    throw(msg);
  }
  this->sendCommandToServer(command_msg);
  //get length of str input
  int length;
    int n = read(channel_->getClientSocket(), &length, sizeof(length));
    if (n == -1) {
      throw(errorReadingFromSocket());
    }
  //get str input of list of games
  string str;
  char letter;
  while (length >0) {
    n = read(channel_->getClientSocket(), &letter, sizeof(letter));
    if (n == -1) {
      throw(errorReadingFromSocket());
    }
    str.append(1,letter);
    length -= 1;
  }
  //print list of games
  if (str.empty()) {
	  this->printer_.printMessage("There are no available games/n");
  } else {
	  this->printer_.printMessage(str);
  }
}

bool OnlineGamePreparer::startOnlineGame(string command, string gameName) {
	stringstream stream;
	stream << command << " " << gameName;
	if (strcmp(command.c_str(), "start")) {
		return this->startOnlineGame(stream.str());
	}
	return this->startOnlineGame(stream.str());


}


bool OnlineGamePreparer::startOnlineGame(string command_msg) {
  //connect to server
  try {
    this->channel_ = this->openCommunicationChannel();
    this->channel_->connectToServer(printer_);
  } catch (const char *msg) {
    throw(msg);
  }
  //send start command to server
  int result;
  this->sendCommandToServer(command_msg);
  cout <<"reading from server" <<endl;

  int n = read(channel_->getClientSocket(), &result, sizeof(result));
  if (n == -1) {
    throw(errorReadingFromSocket());
  }

  cout <<"finished reading from server" <<endl;

  stringstream sstream(command_msg);
  string game_name;
  string command_type;
  sstream >> command_type;
  sstream >> game_name;
  if (result == -1) {
    printer_.printMessage(invalidGame(command_type, game_name));
    return false;
  } else {
    return true;
  }
}


CommunicationChannel* OnlineGamePreparer::openCommunicationChannel() {
  //get server IP and port from file
  ifstream server_info;
  server_info.open("server_info.txt");
  if(!server_info.is_open()) {
    throw(errorOpeningFile());
  }
  string server_IP;
  getline(server_info, server_IP);
  int port_num;
  server_info >> port_num;
  server_info.close();
  CommunicationChannel* channel = new CommunicationChannel(server_IP, port_num);
  return channel;
}

void OnlineGamePreparer::sendCommandToServer(string command_msg) {
  int length = strlen(command_msg.c_str());
  int n = write(channel_->getClientSocket(), &length, sizeof(length));
  if (n == -1) {
    throw(errorWritingToSocket());
  }
  n = write(channel_->getClientSocket(), command_msg.c_str(), length);
  if (n == -1) {
    throw(errorWritingToSocket());
  }
}
