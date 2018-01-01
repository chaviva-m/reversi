/*
 * CommunicationChannel.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include <CommunicationChannel.h>
using namespace std;
using namespace message;

CommunicationChannel::CommunicationChannel(string serverIP, int serverPort):
    serverIP_(serverIP), serverPort_(serverPort), clientSocket_(0) {}

void CommunicationChannel::connectToServer(Printer& printer) {
  // Create a socket point
  clientSocket_ = socket(AF_INET, SOCK_STREAM, 0);
  if (clientSocket_ == -1) {
    throw "Error opening socket";
  }
  // Convert the ip string to a network address
  struct in_addr address;
  if (inet_aton(serverIP_.c_str(), &address) == 0) {
    throw "Can't parse IP address. IP address is invalid";
  }
  // Get a hostent structure for the given host address
  struct hostent *server;
  server = gethostbyaddr((const void *)&address, sizeof
      address, AF_INET);
  if (server == NULL) {
    throw "Host is unreachable";
  }
  // Create a structure for the server address
  struct sockaddr_in serverAddress;
  bzero((char *)&address, sizeof(address));
  serverAddress.sin_family = AF_INET;
  memcpy((char *)&serverAddress.sin_addr.s_addr, (char
      *)server->h_addr, server->h_length);
  // htons converts values between host and network byte orders
  serverAddress.sin_port = htons(serverPort_);
  // Establish a connection with the TCP server
  if (connect(clientSocket_, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
    throw "Error connecting to server";
  }
}

int CommunicationChannel::getClientSocket() {
  return this->clientSocket_;
}
void CommunicationChannel::closeClientSocket() {
	close(this->clientSocket_);
}
