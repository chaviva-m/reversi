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
  try {
	GameSetUp g = GameSetUp();
	g.playGame();
  } catch (const char *msg) {
	cout << "Error in Reversi:main. Reason: " << msg << endl;
  }
  return 0;
}
