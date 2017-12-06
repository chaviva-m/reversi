/*
 * main.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include "GameSetUp.h"
#include "Player.h"
#include "HumanPlayer.h"

//run game
int main() {
  GameSetUp g = GameSetUp();
  g.playGame();
}

#include "Client.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;



Point convertStrToPoint(string& input) {
  int r = 0, c = 0;
  bool startOneNum = false;
  bool finishOneNum = false;
  for (unsigned int i = 0; i < input.size(); i++) {
    if (isdigit(input.at(i))) {
      int k = (int)input[i] - 48;
      if (!finishOneNum) {
        startOneNum = true;
        r = r*10 + k;
      } else {
        c = c*10 + k;
      }
    } else if (startOneNum) {
      finishOneNum = true;
    }
  }
  return (Point(r,c));//needs minus -1 each
}

//int main()
void Clientmain() {
	Client client("127.0.0.1", 8000);//read from file
	try {
		client.connectToServer();
	} catch (const char *msg) {
		cout << "Failed to connect to server. Reason:" << msg << endl;
		exit(-1);
	}

	int row, col, status, rivalStat;
	char sep;
	int r;


	cout << "Waiting for another player to join..."<<endl;
	int color;
	int dummy = read(client.clientSocket, &color, sizeof(color));
	cout << "you'r color is: " << color<<endl;

	if (color == 2) {
		//reading from server

		cout << "Waiting for the other player's move..."<<endl;
		//char result1;
		r = read(client.clientSocket, &rivalStat, sizeof(rivalStat));
		if (r == -1) {
			cout << "Error reading rivalStat" << endl;
		}
		cout << "other player's status is: " << rivalStat << endl;

		if (rivalStat == NO_MOVES) {
			//do nothing
		} else if (rivalStat == HAS_MOVE) {
		    // Read move arguments
			r = read(client.clientSocket, &row, sizeof(row));
			if (r == -1) {
				cout << "Error reading row" << endl;
				return false;
			}
			r = read(client.clientSocket, &sep, sizeof(sep));
			if (r == -1) {
				cout << "Error reading separator" << endl;
				return false;
			}
			r = read(client.clientSocket, &col, sizeof(col));
			if (r == -1) {
				cout << "Error reading col" << endl;
				return false;
			}
			cout << "Player's move is: " << row << ", " << col<< endl;
		} else if (rivalStat == END) {
			cout << "Other player ended the game. Closing client socket" << endl;
			close(client.clientSocket);
			return 0;
		}
	}


	while (true) {
		//writing to server

		// must get 0 or 1 or 2. not checking for back input
		cout << "Enter your decision (0 - no moves, 1- has move, 2- end game):";
		cin >> status;
		cout << "Sending status: ";
	    cout << status << endl;
		try {
			client.sendStatus(status);
		} catch (const char *msg) {
			cout << "Failed to send status to server. Reason: " << msg << endl;//***
		}

		if (status == NO_MOVES) {
			//do nothing
		} else if (status == HAS_MOVE) {
			string input;
			cout << "insert your move 'row,col'" << endl;
			cin >> input;
			Point p = convertStrToPoint(input);
			row = p.getRow();
			col = p.getCol();
			cout << "Sending move: ";
		    cout << p << endl;
			try {
				client.sendMove(row, col);
			} catch (const char *msg) {
				cout << "Failed to send status to server. Reason: " << msg << endl;//***
			}
		} else if (status == END) {
			cout << "Closing client socket" << endl;
			close(client.clientSocket);
			break;
		}



		//reading from server
		cout << "Waiting for the other player's move..."<<endl;
		r = read(client.clientSocket, &rivalStat, sizeof(rivalStat));
		if (r == -1) {
			cout << "Error reading rivalStat" << endl;
		}
		cout << "other player's status is: " << rivalStat << endl;


		if (rivalStat == NO_MOVES) {
			//do nothing
		} else if (rivalStat == HAS_MOVE) {
		    // Read move arguments
			r = read(client.clientSocket, &row, sizeof(row));
			if (r == -1) {
				cout << "Error reading row" << endl;
				return false;
			}
			r = read(client.clientSocket, &sep, sizeof(sep));
			if (r == -1) {
				cout << "Error reading separator" << endl;
				return false;
			}
			r = read(client.clientSocket, &col, sizeof(col));
			if (r == -1) {
				cout << "Error reading col" << endl;
				return false;
			}
			cout << "Player's move is: " << row << ", " << col<< endl;

		} else if (rivalStat == END) {
			cout << "Other player ended the game. Closing client socket" << endl;
			close(client.clientSocket);
			break;
		}
	}
}

