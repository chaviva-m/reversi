/*
 * GameSetUp.h
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
 */

#ifndef GAMESETUP_H_
#define GAMESETUP_H_

#include <map>
#include <vector>

#include "GameFlow.h"
#include "GameLogic.h"
#include "HumanPlayer.h"
#include "messages.h"
#include "Player.h"
#include "Printer.h"
#include "ConsolePrinter.h"
#include "StandardGameLogic.h"

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
  GameSetUp(int board_rows = 8, int board_cols = 8);
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

  std::map<Color,Player*> consolePlayers();

  Board* board_;
  GameLogic* logic_;
  Printer* printer_;
  std::map<Color,Player*> players_;
};

#endif /* GAMESETUP_H_ */
