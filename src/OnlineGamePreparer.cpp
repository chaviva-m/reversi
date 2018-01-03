/*
 * OnlinePlayersCreator.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include "OnlineGamePreparer.h"
using namespace std;
using namespace message;

OnlineGamePreparer::OnlineGamePreparer(Printer& printer,
    CommunicationChannel* channel) : printer_(printer), channel_(channel) {
  this->prepareOnlineGame();
}

void OnlineGamePreparer::throwError(const char* msg) {
	if (this->channel_!= NULL) {
		this->deleteChannel();
	}
	throw msg;
}

void OnlineGamePreparer::prepareOnlineGame() {
  this->gameMenu();
  //get name
  map<Color,Player*> players;
  string name;
  while(name.empty()) {
    this->printer_.printMessage(getPlayerName(LAST_COLOR));
    getline(cin, name);
  }
  printer_.printMessage(waitingForAnotherPlayer());
  //get color from server
  int color;
  int n = read(channel_->getClientSocket(), &color, sizeof(color));
  if (n == -1) {
	  throwError("Error reading from socket.\n");
//    throw("Error reading from socket.\n");
  } else if (n == 0) {
	  throwError("Something went wrong with the server.\n");
	  //    throw("Something went wrong with the server.\n");
    return;
  } else if (color < 0) {
	  throwError("Something went wrong with the server.\n");
//	  throw("Something went wrong with the server.\n");
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
CommunicationChannel* OnlineGamePreparer::getChannel() {
	return this->channel_;
}

std::map<Color,Player*> OnlineGamePreparer::getOnlinePlayers() {
  return this->players_;
}

int OnlineGamePreparer::convertStrToInt(const string& input) const {
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

void OnlineGamePreparer::gameMenu() {
  int input;
  string command;
  bool valid_input = false;
  bool started_game = false;

  do {
    this->printer_.printMessage(onlineGameMenu());
    getline(cin, command);
    input = convertStrToInt(command);
    switch(input) {
		  case(START_GAME):
    	      valid_input = true;
	        started_game = this->startOnlineGame("start");
	        break;
		  case(LIST_GAMES):
		      valid_input = true;
		      this->listAvailableOnlineGames("list_games");
		      break;
		  case(JOIN_GAME):
    	    valid_input = true;
			  started_game = this->startOnlineGame("join");
			  break;
		  default:
		    printer_.printMessage(invalidInput());
		    break;
    }
  } while(!started_game || !valid_input);
}

void OnlineGamePreparer::listAvailableOnlineGames(const string& command_msg) {
  //connect to server
	this->creatChannel();

  this->sendCommandToServer(command_msg);
  //get length of str input
  int length;
    int n = read(channel_->getClientSocket(), &length, sizeof(length));
    if (n == -1) {
//	  this->deleteChannel();
	  throwError("Something went wrong with the server.\n");
//      throw("Something went wrong with the server.\n");
    } else if (n == 0) {
//	  this->deleteChannel();
	  throwError("Something went wrong with the server.\n");
//      throw("Something went wrong with the server.\n");
    }
  //get str input of list of games
  string str;
  char letter;
  while (length >0) {
    n = read(channel_->getClientSocket(), &letter, sizeof(letter));
    if (n == -1) {
//	  this->deleteChannel();
	  throwError("Error reading from socket.\n");
      throw("Error reading from socket.\n");
    } else if (n == 0) {
//	  this->deleteChannel();
    	throwError("Something went wrong with the server.\n");
//      throw("Something went wrong with the server.\n");
    }
    str.append(1,letter);
    length -= 1;
  }
  //print list of games
  this->printer_.printMessage("\n");
  this->printer_.printMessage(str);
  this->printer_.printMessage("\n");
  this->deleteChannel();
}
void OnlineGamePreparer::creatChannel() {
	//new CommunicationChannel
	this->channel_ = this->openCommunicationChannel();
	try {
		this->channel_->connectToServer(printer_);
	} catch (const char *msg) {
		throwError(msg);
//		this->deleteChannel();
//		throw(msg);
	}
}
void OnlineGamePreparer::deleteChannel() {
	delete channel_;
}

bool OnlineGamePreparer::startOnlineGame(const string& command) {
  //connect to server
	this->creatChannel();

  string game_name;
  while(game_name.empty()) {
    this->printer_.printMessage(enterGameName());
    getline(cin, game_name);
  }

  stringstream command_msg;
  command_msg << command << " " << game_name;

  //send start command to server
  int result;
  this->sendCommandToServer(command_msg.str());

  int n = read(channel_->getClientSocket(), &result, sizeof(result));
  if (n == -1) {
//	this->deleteChannel();
	throwError("Error reading from socket.\n");
//    throw("Error reading from socket.\n");
  } else if (n == 0) {
//	 this->deleteChannel();
	  throwError("Something went wrong with the server.\n");
//	  throw("Something went wrong with the server.\n");
  }

  if (result == -1) {
    printer_.printMessage("\n");
    printer_.printMessage(invalidGame(command, game_name));
    printer_.printMessage("\n");
    this->deleteChannel();
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
	  throwError("Cannot open file with server information.\n");
//    throw("Cannot open file with server information.\n");
  }
  string server_IP;
  getline(server_info, server_IP);
  int port_num;
  server_info >> port_num;
  server_info.close();
  CommunicationChannel* channel = new CommunicationChannel(server_IP, port_num);
  return channel;
}

void OnlineGamePreparer::sendCommandToServer(const string& command_msg) {
  int length = strlen(command_msg.c_str());
  int n;

  //ignore broken pipe signal, if server is closed result of write will be -1
  signal(SIGPIPE, SIG_IGN);

  //write length of command
  n = write(channel_->getClientSocket(), &length, sizeof(length));
  if (n == -1) {
	  throwError("something went wrong with the server.\n");
//    throw("something went wrong with the server.\n");
  }
  //write command
  n = write(channel_->getClientSocket(), command_msg.c_str(), length);
  if (n == -1) {
	  throwError("something went wrong with the server.\n");
//    throw("something went wrong with the server.\n");
  }
}
