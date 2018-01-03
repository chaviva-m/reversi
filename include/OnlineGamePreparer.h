/*
 * OnlinePlayersCreator.h
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
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

#include <csignal>
#include <fstream>
#include <iostream>
#include <map>
#include <limits>
#include <poll.h>
#include <string>
#include <vector>

class OnlineGamePreparer {
public:
  /*
   * constructor
   */
  OnlineGamePreparer(Printer& printer, CommunicationChannel* channel);
  /*
   * destructor
   */
  virtual ~OnlineGamePreparer() {};
  /*
   * access online playeres
   */
  std::map<Color,Player*> getOnlinePlayers();
  /*
   * returns the address of the CommunicationChannel
   */
  CommunicationChannel* getChannel();


private:
  /*
   * prepare game
   */
  void prepareOnlineGame();
  /*
   * display game options to user
   */
  void gameMenu();
  /*
   * sends user's request to server.
   */
  void sendCommandToServer(const string& command_msg);
  /*
   * start online game.
   */
  bool startOnlineGame(const string& command);
  /*
   * inform user of available online games that he/she can join.
   */
  void listAvailableOnlineGames(const string& command_msg);
  /*
   * open connection channel with server IP and port from file.
   * output: CommunicationChannel*
   */
  CommunicationChannel* openCommunicationChannel();
  /*
   * input: a string.
   * output: if the input contains an integer (even separated)- this func will
   * return int. else- return 0.
   */
  int convertStrToInt(const string& input) const;
  /*
   * create a communication channel
   */
  void creatChannel();
  /*
   *delete the allocated communication channel
   */
  void deleteChannel();

  void throwError(const char* msg);


  //data members
  std::map<Color,Player*> players_;
  Printer& printer_;
  CommunicationChannel* channel_;
};

#endif /* INCLUDE_ONLINEGAMEPREPARER_H_ */
