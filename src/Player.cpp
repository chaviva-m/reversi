/*
 * Player.cpp
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#include "Player.h"
using namespace std;

Player::Player(const string& name, Color color) : name_(name), color_(color) {
}

string Player::getName() const {
  return this->name_;
}

Color Player::getColor() const {
  return this->color_;
}

void Player::insertDisk(Cell& cell) const {
  cell.insertDisk(this->color_);
}

void Player::flipDisks(const vector<Cell*>& cells_to_flip) const {
  for (unsigned i = 0; i < cells_to_flip.size(); i++) {
    cells_to_flip[i]->getDisk()->flipDisk();
  }
}
