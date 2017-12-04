/*
 * main.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

//#include "GameSetUp.h"
//#include "Player.h"
//#include "HumanPlayer.h"
//
////run game
//int main() {
//  GameSetUp g = GameSetUp();
//  g.playGame();
//}


#include "Client.h"
#include <iostream>
#include <stdlib.h>



#include "Client.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
using namespace std;

int main() {
	Client client("127.0.0.1", 8000);//read from file
	try {
		client.connectToServer();
	} catch (const char *msg) {
		cout << "Failed to connect to server. Reason:" << msg << endl;
		exit(-1);
	}

//
//	char message[80];
//	int dummy = read(client.clientSocket, message, 80);
//	cout << message<<endl;

	cout << "Waiting for another player to join..."<<endl;
	int color;
	int dummy = read(client.clientSocket, &color, sizeof(color));
	cout << "you'r color is: " << color<<endl;

	if (color == 2) {
		cout << "Waiting for the other player's move..."<<endl;
		//char result1;
		int result1;
		int dummy = read(client.clientSocket, &result1, sizeof(result1));
		cout << "other player's result is: " << result1 << endl;
	}
	int num1, num2;
	char op;
//	cout << "Enter an exercise (e.g., 15*19):";
//	cin >> num1 >> op >> num2;
//	cout << "Sending exercise: " << num1 << op<< num2 << endl;
//	try {
//		int result = client.sendExercise(num1,op, num2);
//		cout << "Result: " << result << endl;
//	} catch (const char *msg) {
//		cout << "Failed to send exercise to server. Reason: " << msg << endl;
//	}

//	int num1, num2;
//	char op;
	while (true) {

		cout << "Enter an exercise (e.g., 15*19):";
		cin >> num1 >> op >> num2;
		cout << "Sending exercise: " << num1 << op<< num2 << endl;
		try {
			int result = client.sendExercise(num1,op, num2);
			cout << "Result: " << result << endl;
		} catch (const char *msg) {
			cout << "Failed to send exercise to server. Reason: " << msg << endl;
		}

		cout << "Waiting for the other player's move..."<<endl;
		//char result1;
		int result1;
		int dummy = read(client.clientSocket, &result1, sizeof(result1));
		cout << "other player's result is: " << result1 << endl;

//		string player2move;
//		int dummy = read(client.clientSocket, &player2move, sizeof(player2move));
//		cout <<player2move<<endl;
	}
}
