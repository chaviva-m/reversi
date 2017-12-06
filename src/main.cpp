/*
 * main.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include "GameSetUp.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "messages.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

//run game
int main() {
  GameSetUp g = GameSetUp();
  g.playGame();
}
