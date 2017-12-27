/*
 * OnlinePlayersCreator.h
 *
 *  Created on: Dec 26, 2017
 *      Author: chaviva
 */

#ifndef INCLUDE_ONLINEGAMEPREPARER_H_
#define INCLUDE_ONLINEGAMEPREPARER_H_

#include "CommunicationChannel.h"
#include "ConsolePrinter.h"
#include "LocalOnlinePlayer.h"
#include "messages.h"
#include "onlineOptionEnums.h"
#include "Player.h"
#include "Printer.h"
#include "RemoteOnlinePlayer.h"

#include <fstream>
#include <iostream>
#include <map>
#include <limits>
#include <string>
#include <vector>

class OnlineGamePreparer {
public:
  OnlineGamePreparer(Printer& printer, CommunicationChannel* channel);
  virtual ~OnlineGamePreparer() {};
  std::map<Color,Player*> getOnlinePlayers();

private:
  void prepareOnlineGame();
  void remotePlayerMenu();
  /*
   * sends user's request to server.
   */
  void sendCommandToServer(string command_msg);
  /*
   * start online game.
   */
  bool startOnlineGame(string command_msg);
  /*
   * inform user of available online games that he/she can join.
   */
  void listAvailableOnlineGames(string command_msg);
  /*
   * open connection channel with server IP and port from file.
   * output: CommunicationChannel*
   */
  CommunicationChannel* openCommunicationChannel();

  //data members
  std::map<Color,Player*> players_;
  Printer& printer_;
  CommunicationChannel* channel_;
};

#endif /* INCLUDE_ONLINEGAMEPREPARER_H_ */
