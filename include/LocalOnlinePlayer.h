/*
 * LocalOnlinePlayer.h
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#ifndef INCLUDE_LOCALONLINEPLAYER_H_
#define INCLUDE_LOCALONLINEPLAYER_H_

#include "color.h"
#include "CommunicationChannel.h"
#include "HumanPlayer.h"
#include "messages.h"
#include "Point.h"

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <netdb.h>
#include <poll.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
/*
 * Local online player. A Human player that can send messages to the server.
 */
class LocalOnlinePlayer: public HumanPlayer {
public:
  /*
   * Constructs Local Online Player with name, color and communication channel
   */
  LocalOnlinePlayer(const std::string& name, Color color,
                    CommunicationChannel& channel);
  /*
   * finishes player's turn, send message to server with move
   */
  virtual void endTurn(Point* move, Printer& printer) const;
  /*
   * send message to server that game is over
   */
  virtual void endGame(Printer& printer) const;
  /*
   * checks if server socket is closed.
   */
  bool is_server_closed(const int cs) const;
  /*
   * destructor
   */
  virtual ~LocalOnlinePlayer() {};

private:
  CommunicationChannel& channel_;
  void sendMove(int row, int col, Printer& printer) const;
  void sendMove(Status stat, Printer& printer) const;
};

#endif /* INCLUDE_LOCALONLINEPLAYER_H_ */
