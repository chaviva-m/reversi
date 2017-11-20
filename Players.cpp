/*
 * Players.cpp
 *
 * Author: djoffe
 * Dana Joffe
 * ID 312129240
 */
#include "Players.h"

Player::~Player() {}
HumanPlayer::~HumanPlayer() {}
HumanPlayer::HumanPlayer(const HumanPlayer &oldHumanPlayer) {
	this->color = oldHumanPlayer.getColor();
}

HumanPlayer* HumanPlayer::clone () {
	return new HumanPlayer(*this);
}

HumanPlayer::HumanPlayer(PlayerEnum color): color(color) {}
const PlayerEnum HumanPlayer::getColor() const {
	return this->color;
}

Location HumanPlayer::convertStrToLocation(string& input) {
	int r = 0, c = 0;
	int er = 0, ec = 0;
	bool startOneNum = false;
	bool finishOneNum = false;
	for (unsigned int i = 0; i < input.size(); i++) {
		if (isdigit(input.at(i))) {
			int k = (int)input[i] - 48;
			if (!finishOneNum) {
				startOneNum = true;
				r = r*(10^er) + k;
			} else {
				c = c*(10^ec) + k;
			}
		} else if (startOneNum) {
			finishOneNum = true;
		}
	}
	return (Location(r,c));
}

Location HumanPlayer::decideOnAmove(Board& board, set<Location>& possibleMoves){
	string location;
	getline(cin, location);
	Location loc = this->convertStrToLocation(location);
	return loc;

}
