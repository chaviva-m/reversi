/*
 * Client.h
 *
 *  Created on: Dec 3, 2017
 *      Author: djoffe
 */

#ifndef INCLUDE_CLIENT_H_
#define INCLUDE_CLIENT_H_

enum Input {NO_MOVES, HAS_MOVE, END};

class Client {
public:
	Client(const char *serverIP, int serverPort);
	void connectToServer();
	void sendExercise(int arg1, char op, int arg2);
	int getResault();
	int clientSocket;
	void sendStatus(int stat);
	void sendMove(int row, int col);

private:
	const char *serverIP;
	int serverPort;
};


#endif /* INCLUDE_CLIENT_H_ */
