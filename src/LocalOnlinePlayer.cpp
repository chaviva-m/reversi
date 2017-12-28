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

	//write size to server
	int size = strlen(msg.str().c_str());
	int n;
	if (!this->is_server_closed(channel_.getClientSocket())) {
	  n = write(channel_.getClientSocket(), &size, sizeof(size));
	  if (n == -1) {
	    printer.printMessage(errorWritingToSocket());
	    endGame(printer);
	  }
	} else {
	  throw("something went wrong with the server.\n");
	}

	//write move to server
	if (!this->is_server_closed(channel_.getClientSocket())) {
	  n = write(channel_.getClientSocket(), msg.str().c_str(), strlen(msg.str().c_str()));
	  if (n == -1) {
	    printer.printMessage(errorWritingToSocket());
	    endGame(printer);
	  }
	} else {
	  throw("something went wrong with the server.\n");
	}
}

void LocalOnlinePlayer::sendMove(Status stat, Printer& printer) const {
	if (stat == NO_MOVES){
		sendMove(-1, -1, printer);
	} else if (stat == END) {

		string msg = "close";
		int size = strlen(msg.c_str());

		// write length
		int n;
		if (!this->is_server_closed(channel_.getClientSocket())) {
		  n = write(channel_.getClientSocket(), &size, sizeof(size));
	    if (n == -1) {
	      printer.printMessage(errorWritingToSocket());
	    }
	  } else {
	    throw("something went wrong with the server.\n");
	  }

		// write message
		if (!this->is_server_closed(channel_.getClientSocket())) {
		  n = write(channel_.getClientSocket(), msg.c_str(), strlen(msg.c_str()));
	    if (n == -1) {
	      printer.printMessage(errorWritingToSocket());
	    }
		} else {
      throw("something went wrong with the server.\n");
    }
	}
}

void LocalOnlinePlayer::endGame(Printer& printer) const {
	sendMove(END, printer);//send close
}

bool LocalOnlinePlayer::is_server_closed(const int cs) const {
  pollfd pfd;
  pfd.fd = cs;
  pfd.events = POLLIN | POLLHUP | POLLRDNORM;
  pfd.revents = 0;

  // call poll with a timeout of 100 ms
  if(poll(&pfd, 1, 100) > 0) {
    // if result > 0, this means that there is either data available on the
    // socket, or the socket has been closed
    char buffer[32];
    if(recv(cs, buffer, sizeof(buffer), MSG_PEEK | MSG_DONTWAIT) == 0) {
      // if recv returns zero, that means the connection has been closed:
      return true;
    }
  }
  return false;
}
