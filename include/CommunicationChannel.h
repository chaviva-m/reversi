/*
 * CommunicationChannel.h
 *
 *  Created on: Dec 6, 2017
 *      Author: chaviva
 */

#ifndef INCLUDE_COMMUNICATIONCHANNEL_H_
#define INCLUDE_COMMUNICATIONCHANNEL_H_

#include "messages.h"
#include "Printer.h"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

class CommunicationChannel {
public:
  CommunicationChannel(string serverIP, int serverPort);
  void connectToServer(Printer& printer);
  int getClientSocket();

private:
  string serverIP_;
  int serverPort_;
  int clientSocket_;
};

#endif /* INCLUDE_COMMUNICATIONCHANNEL_H_ */
