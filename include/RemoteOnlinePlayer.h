/*
 * RemoteOnlinePlayer.h
 *
 *  Created on: Dec 6, 2017
 *      Author: chaviva
 */

#ifndef INCLUDE_REMOTEONLINEPLAYER_H_
#define INCLUDE_REMOTEONLINEPLAYER_H_

#include "Point.h"
#include "Player.h"
#include "color.h"
#include "CommunicationChannel.h"
#include "messages.h"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

class RemoteOnlinePlayer: public Player {
public:
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
      GameLogic& logic, Printer& printer); //pass Printer
  /*
   * informs the player that he has no moves to execute.
   */
  virtual void hasNoMoves(Printer& printer); //pass printer
  /*
   * finishes player's turn
   */
  virtual void endTurn(Point* move, Printer& printer) const; //pass Printer
  /*
   * send message to server that game is over
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
