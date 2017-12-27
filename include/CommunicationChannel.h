/*
 * CommunicationChannel.h
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
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
/*
 * Communication Channel has server IP, server port and client socket.
 * It can connect to the server.
 */
class CommunicationChannel {
public:
  /*
   * Communication Channel constructor
   * input: string serverIP, int serverPort
   */
  CommunicationChannel(string serverIP, int serverPort);
  /*
   * Connects to the server
   * input: Printer& printer
   */
  void connectToServer(Printer& printer);
  /**
   * access client socket
   */
  int getClientSocket();


  void closeClientSocket();


private:
  string serverIP_;
  int serverPort_;
  int clientSocket_;
};

#endif /* INCLUDE_COMMUNICATIONCHANNEL_H_ */
