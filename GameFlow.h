/*
 * GameFlow.h
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
 */

#ifndef GAMEFLOW_H_
#define GAMEFLOW_H_

#include <algorithm>
#include <map>
#include <vector>

#include "Board.h"
#include "color.h"
#include "GameLogic.h"
#include "messages.h"
#include "Player.h"
#include "Printer.h"

/**
 * controls flow of game
 */
class GameFlow {
public:
  /**
   * constructs game flow with board, game logic, players and printer
   * input: Board& board, GameLogic& logic,
   *        std::map<Color, Player*> players, Printer& printer
   * output: void
   */
  GameFlow(Board& board, GameLogic& logic,
            const std::map<Color, Player*>& players, Printer& printer);
  /**
   * play game
   * input: void
   * output: void
   */
  void playGame();

private:
  /**
   * initialize board with 4 disks in center: 2 of each color
   * input: void
   * output: void
   */
  void initializeBoard();
  /**
   * play one round of game, one turn for each player
   * input: void
   * output: false if game is over (board is full or
   * neither player has possible moves), otherwise true
   */
  bool playOneRound();
  /**
   * end of game
   * input: void
   * output: void
   */
  void endGame();
  /**
   * player with more disks of his/her color is the winner
   * input: void
   * output: Player* winner or NULL if players tied
   */
  Player* determineWinner();
  Board& board_;
  GameLogic& logic_;
  std::map<Color,Player*> players_;
  Printer& printer_;
  int num_disks_played_;
};

#endif /* GAMEFLOW_H_ */
