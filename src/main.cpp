/*
 * main.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include "GameSetUp.h"

#include <iostream>

using namespace std;

//run game
int main() {
	GameSetUp g = GameSetUp(4,4);
  try {
    g.setPlayers();
	g.playGame();
  } catch (const char* msg) {
    cout << endl << msg << endl;
    return 0;
  }
  return 0;
}
