/*
 * Client.h
 *
 *  Created on: Dec 3, 2017
 *      Author: djoffe
 */

#ifndef INCLUDE_CLIENT_H_
#define INCLUDE_CLIENT_H_


class Client {
public:
	Client(const char *serverIP, int serverPort);
	void connectToServer();
	int sendExercise(int arg1, char op, int arg2);
	int clientSocket;

private:
	const char *serverIP;
	int serverPort;
};


#endif /* INCLUDE_CLIENT_H_ */
