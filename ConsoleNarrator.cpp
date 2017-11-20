/*
 * ConsoleNarrator.cpp
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
 */

#include "ConsoleNarrator.h"
using namespace std;
ConsoleNarrator::ConsoleNarrator() {
}

const string ConsoleNarrator::getPlayerName(Color color) {
  cout << "Player " << color << " please enter your name: ";
  string name;
  cin >> name;
  return name;
}

void ConsoleNarrator::printBoard(const Board& board) {
  cout << "Current board:" << endl;
  board.printBoardToConsole();
}

void ConsoleNarrator::startTurn(const string& player) {
  cout << player << ": It's your turn." << endl;
}

const Point ConsoleNarrator::getMove(const vector<Cell*>& moves) {
  int row, col;
  while (true) {
    cout << "Your possible moves: ";
    cout << moves[0]->getLocation();
    for (unsigned i = 1; i < moves.size(); i++) {
      cout << "," << moves[i]->getLocation();
    }
    cout << endl;
    cout << "Please enter your move as follows: row column ";
    cin >> row >> col;
    if(!cin.fail()) {
      return Point(row, col);
   }
    this->invalidInput();
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}

void ConsoleNarrator::noPossibleMoves() {
  cout << "No possible moves." << endl;
  cout << "Play passes back to the other player." << endl;
  cout << "Press any key and then Enter to continue" << endl;
  char any_key;
  cin >> any_key;
}

void ConsoleNarrator::invalidInput() {
  cout << "invalid input" << endl;
}

void ConsoleNarrator::declareWinner(const string& winner) {
  cout << "Game over. The winner is... " << winner << "!" << endl;
}

void ConsoleNarrator::declareTie() {
  cout << "Game over. It's a tie!" << endl;
}

ConsoleNarrator::~ConsoleNarrator() {}
