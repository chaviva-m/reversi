/*
 * GameSetUp.h
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#ifndef GAMESETUP_H_
#define GAMESETUP_H_

#include <map>
#include <vector>
#include "CommunicationChannel.h"
#include "ConsolePrinter.h"
#include "GameFlow.h"
#include "GameLogic.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "messages.h"
#include "Player.h"
#include "PresentOnlinePlayer.h"
#include "Printer.h"
#include "StandardGameLogic.h"
#include "RemoteOnlinePlayer.h"
#include "rival.h"

/**
 * sets up and starts game
 */
class GameSetUp {
public:
  /**
   * construct game set up with board of board_rows x board_cols,
   * game logic, narrator and players
   * input: int board_rows (default: 8), int board_cols (default: 8)
   * output: void
   */
  GameSetUp(int board_rows = DEFAULT_ROWS, int board_cols = DEFAULT_COLS);
  /**
   * play game
   * input: void
   * output: void
   */
  void playGame() const;
  /**
   * destructs game set up
   * input: void
   * output: void
   */
  ~GameSetUp();

private:
  /**
   * return standard game logic
   * input: void
   * output: GameLogic*
   */
  GameLogic* standardLogic();
  /**
   * return printer for console
   * input: void
   * output: Printer*
   */
  Printer* consoleInterface();
  /*
   * generates a solo console player and a computer AI player.
   * input: void
   * output: a map of players and their representative color.
   */
  std::map<Color,Player*> AIAndConsolePlayers();
  /*
   * generates two console players.
   * input: void
   * output: a map of players and their representative color.
   */
  std::map<Color,Player*> consolePlayers();
  /*
   * generates online players.
   * input: void
   * output: a map of players and their representative color.
   */
  std::map<Color, Player*> onlinePlayers();
  /*
   * asks the user the kind of player he wants to play with, and respectively
   * set the game players in GamesetUp.
   */
  void setPlayersMenu();
  /*
   * input: a string.
   * output: if the input contains an integer (even separated)- this func will
   * return it. else- return 0.
   */
  int convertStrToPoint(string& input);
  static const int DEFAULT_ROWS = 8;
  static const int DEFAULT_COLS = 8;
  Board* board_;
  GameLogic* logic_;
  Printer* printer_;
  std::map<Color,Player*> players_;

  CommunicationChannel* channel_ = NULL;
};

#endif /* GAMESETUP_H_ */
