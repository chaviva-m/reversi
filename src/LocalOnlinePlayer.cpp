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
//	cout<<"LocalOnlinePlayer::sendMove"<<endl;

	stringstream msg;
	msg << "play" << " " << row << " " << col;
	int size = strlen(msg.str().c_str());
	int n = write(channel_.getClientSocket(), &size, sizeof(size));
	if (n == -1) {
		printer.printMessage(errorWritingToSocket());
		endGame(printer);
	}
	if (n == 0) {
		printer.printMessage("Exception: server is closed");
		throw "Exception: server is closed";
	}
	n = write(channel_.getClientSocket(), msg.str().c_str(), strlen(msg.str().c_str()));
	if (n == -1) {
		printer.printMessage(errorWritingToSocket());
		endGame(printer);
	}
}

void LocalOnlinePlayer::sendMove(Status stat, Printer& printer) const {
	if (stat == NO_MOVES){
		sendMove(-1, -1, printer);
	} else if (stat == END) {
//		sendMove(-2, -2, printer);

		cout << "writing 'close' to server" <<endl;

		string msg = "close";
		int size = strlen(msg.c_str());

		// write length
		int n = write(channel_.getClientSocket(), &size, sizeof(size));
		if (n == -1) {
			printer.printMessage(errorWritingToSocket());
			endGame(printer);
		}

		// write message
		n = write(channel_.getClientSocket(), msg.c_str(), strlen(msg.c_str()));
		if (n == -1) {
			printer.printMessage(errorWritingToSocket());
			endGame(printer);
		}
	}
}

void LocalOnlinePlayer::endGame(Printer& printer) const {
	sendMove(END, printer);//send close
}
