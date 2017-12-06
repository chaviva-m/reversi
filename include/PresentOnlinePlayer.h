/*
 * PresentOnlinePlayer.h
 *
 *  Created on: Dec 6, 2017
 *      Author: chaviva
 */

#ifndef INCLUDE_PRESENTONLINEPLAYER_H_
#define INCLUDE_PRESENTONLINEPLAYER_H_

#include "HumanPlayer.h"
#include "color.h"
#include "CommunicationChannel.h"
#include "messages.h"
#include "Point.h"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

class PresentOnlinePlayer: public HumanPlayer {
public:
  PresentOnlinePlayer(const std::string& name, Color color,
                    CommunicationChannel& channel);
  /*
   * finishes player's turn
   */
  virtual void endTurn(Point* move, Printer& printer) const;
  /*
   * send message to server that game is over
   */
  virtual void endGame(Printer& printer);
  /*
   * destructor
   */
  virtual ~PresentOnlinePlayer() {};

  void sendStatus(int stat, Printer& printer) const;
  void sendMove(int row, int col, Printer& printer) const;



protected:
  CommunicationChannel& channel_;
};

#endif /* INCLUDE_PRESENTONLINEPLAYER_H_ */
