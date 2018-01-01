/*
 * RemoteOnlinePlayer.h
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#ifndef INCLUDE_REMOTEONLINEPLAYER_H_
#define INCLUDE_REMOTEONLINEPLAYER_H_

#include "color.h"
#include "CommunicationChannel.h"
#include "messages.h"
#include "Player.h"
#include "Point.h"

#include <csignal>
#include <stdlib.h>
#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

/*
 * Remote online player. A player that gets remote player's moves from server.
 */
class RemoteOnlinePlayer: public Player {
public:
  /*
   * constructs remote online player with name, color and communication channel
   */
  RemoteOnlinePlayer(const std::string& name, Color color,
      CommunicationChannel& channel);
  /*
   * asks the player to decide on a move to execute.
   * input: board- current game board
   *    possibleMoves - move options.
   *    logic - current game logic (game rules).
   * output: the chosen move in Point representation.
   */
  virtual Point decideOnAMove(Board& board, std::vector<Cell*>& possibleMoves,
      GameLogic& logic, Printer& printer);
  /*
   * informs the player that he has no moves to execute.
   */
  virtual void hasNoMoves(Printer& printer);
  /*
   * finishes player's turn
   */
  virtual void endTurn(Point* move, Printer& printer) const;
  /*
   * send message to server that game is over.
   */
  virtual void endGame(Printer& printer);
  /*
   * destructor.
   */
 virtual ~RemoteOnlinePlayer() {};

private:
  CommunicationChannel& channel_;
};

#endif /* INCLUDE_REMOTEONLINEPLAYER_H_ */
