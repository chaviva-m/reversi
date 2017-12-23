/*
 * RemoteOnlinePlayer.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include "RemoteOnlinePlayer.h"

using namespace std;
using namespace message;

RemoteOnlinePlayer::RemoteOnlinePlayer(const string& name, Color color,
    CommunicationChannel& channel) : Player(name, color), channel_(channel) {
}

string readStringFromSocket(int length, int socket) {
	string str;
	int r;
	char letter;
	while (length >0) {
		r = read(socket, &letter, sizeof(letter));
		if (r == -1) {
			throw(errorReadingFromSocket());
		}
		str.append(1,letter);
		length -= 1;
	}
	return str;
}


Status PlayDecoder(string message, int* row, int* col) {
	string buf; // Have a buffer string
	stringstream msg(message); // Insert the string into a stream
	vector<string> tokens; // Create vector to hold our words

	while (msg >> buf)
		   tokens.push_back(buf);

	int num1 = atoi(tokens[1].c_str());
	int num2 = atoi(tokens[2].c_str());

	if(num1 == -1 && num2 == -1) {
		return NO_MOVES;
	} else if(num1 == -2 && num2 == -2) {
		return END;
	} else {
		*row = num1;
		*col = num2;
		return HAS_MOVE;
	}
}

// this method is being called ONLY IF possibleMoves isn't empty.
Point RemoteOnlinePlayer::decideOnAMove(Board& board,
    std::vector<Cell*>& possibleMoves, GameLogic& logic, Printer& printer) {

  printer.printMessage(waitingForMove());
  int row, col;
  int size;
  //read message length
  int r = read(channel_.getClientSocket(), &size, sizeof(size));
  if (r == -1) {
	  throw(errorReadingFromSocket());
  }
  //reading message
  string msg = readStringFromSocket(size ,channel_.getClientSocket()); //throws error
  Status status = PlayDecoder(msg, &row, &col); //read move's arguments

  if(status != HAS_MOVE) {
    throw "Something went wrong with the other player\n";
  }
  return Point(row, col);
}

void RemoteOnlinePlayer::hasNoMoves(Printer& printer) {
	printer.printMessage(waitingForMove());
	int row, col, size;
	//read message length
	int r = read(channel_.getClientSocket(), &size, sizeof(size));
	if (r == -1) {
	   throw(errorReadingFromSocket());
	}
	//reading message
	string msg = readStringFromSocket(size ,channel_.getClientSocket()); //throws error
	Status status = PlayDecoder(msg, &row, &col); //read move's arguments
	if(status != NO_MOVES) {
		throw "Something went wrong with the other player\n";
	}
}

void RemoteOnlinePlayer::endTurn(Point* move, Printer& printer) const {
  if (move != NULL) {
    printer.printMessage(finishTurn(color_, *move));
  } else {
    printer.printMessage(noPossibleMovesForPlayer(color_));
  }
}
