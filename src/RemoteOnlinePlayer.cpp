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
			throw("Game was disconnected.\n");
		} else if (r == 0) {
      throw("Game was disconnected.\n");
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

    //read row
    int r = read(channel_.getClientSocket(), &row, sizeof(row));
    if (r == -1) {
    	throw("Error reading from socket.\n");
    } else if (r == 0) {
      throw("Game was disconnected.\n");
    }

    //read col
    r = read(channel_.getClientSocket(), &col, sizeof(col));
    if (r == -1) {
      throw("Error reading from socket.\n");
    } else if (r == 0) {
      throw("Game was disconnected.\n");
    }

    if (row < 0 || col < 0) {
  	  throw("Game was disconnected.\n");
    }
  return Point(row, col);
}

void RemoteOnlinePlayer::hasNoMoves(Printer& printer) {
	printer.printMessage(waitingForMove());
	int row, col;
	//read row
	int r = read(channel_.getClientSocket(), &row, sizeof(row));
	if (r == -1) {
	    throw("Error reading from socket.\n");
	} else if (r == 0) {
    throw("Game was disconnected.\n");
  }

	//read col
	r = read(channel_.getClientSocket(), &col, sizeof(col));
	if (r == -1) {
	    throw("Error reading from socket.\n");
	} else if (r == 0) {
    throw("Game was disconnected.\n");
  }

	if(row != -1 || col != -1) {
		throw("Game was disconnected.\n");
	}
}

void RemoteOnlinePlayer::endTurn(Point* move, Printer& printer) const {
  if (move != NULL) {
    printer.printMessage(finishTurn(color_, *move));
  } else {
    printer.printMessage(noPossibleMovesForPlayer(color_));
  }
}

void RemoteOnlinePlayer::endGame(Printer& printer) {

  string msg = "close";
  int n;

  //ignore broken pipe signal, if server is closed result of write will be -1
  signal(SIGPIPE, SIG_IGN);

  // write length
  int size = strlen(msg.c_str());
  n = write(channel_.getClientSocket(), &size, sizeof(size));
  if (n == -1) {
    return;
  }

  // write message
  n = write(channel_.getClientSocket(), msg.c_str(), strlen(msg.c_str()));
  if (n == -1) {
    return;
  }

}
