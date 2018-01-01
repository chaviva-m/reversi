/*
 * PresentOnlinePlayer.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include <LocalOnlinePlayer.h>
using namespace message;

LocalOnlinePlayer::LocalOnlinePlayer(const std::string& name, Color color,
    CommunicationChannel& channel) :
    HumanPlayer(name, color), channel_(channel) {}

void LocalOnlinePlayer::endTurn(Point* move, Printer& printer) const {
  if (move == NULL) {
    sendMove(-1, -1, printer);
  } else {
    sendMove(move->getRow(), move->getCol(), printer);
  }
}

void LocalOnlinePlayer::sendMove(int row, int col, Printer& printer) const {

	stringstream msg;
	msg << "play" << " " << row << " " << col;

  int n;

	//ignore broken pipe signal, if server is closed result of write will be -1
  signal(SIGPIPE, SIG_IGN);

	//write size to server
	int size = strlen(msg.str().c_str());
  n = write(channel_.getClientSocket(), &size, sizeof(size));
  if (n == -1) {
    throw("Game was disconnected.\n");
  }

	//write move to server
	n = write(channel_.getClientSocket(), msg.str().c_str(), strlen(msg.str().c_str()));
	if (n == -1) {
    throw("Game was disconnected.\n");
	}
}

void LocalOnlinePlayer::sendMove(Status stat, Printer& printer) const {
	if (stat == NO_MOVES){
		sendMove(-1, -1, printer);
	} else if (stat == END) {

		string msg = "close";
    int n;

	  //ignore broken pipe signal, if server is closed result of write will be -1
    signal(SIGPIPE, SIG_IGN);

		// write length
    int size = strlen(msg.c_str());
		n = write(channel_.getClientSocket(), &size, sizeof(size));
	  if (n == -1) {
	    printer.printMessage(errorWritingToSocket());
	    return;
	  }

		// write message
	  n = write(channel_.getClientSocket(), msg.c_str(), strlen(msg.c_str()));
	  if (n == -1) {
	    printer.printMessage(errorWritingToSocket());
	  }

	}
}

void LocalOnlinePlayer::endGame(Printer& printer) const {
	sendMove(END, printer);//send close
}
