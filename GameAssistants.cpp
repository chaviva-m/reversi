/*
 * GameAssistants.cpp
 *
 * Author: djoffe
 * Dana Joffe
 * ID 312129240
 */
#include "GameAssistants.h"

Counter::~Counter() {}
FlipListener::~FlipListener(){}

FlipCounter::FlipCounter(PlayerEnum player): player(player), sum(2) {}
FlipCounter::~FlipCounter() {}
void FlipCounter::flipOccured(const PlayerEnum from, const PlayerEnum to) {
	if (from == this->player && to != this->player) {
		this->drop();
	}
	if (to == this->player && from != this->player) {
		this->raise();
	}
}
int FlipCounter::total() {
	return sum;;
}
void FlipCounter::raise() {
	sum += 1;
}
void FlipCounter::drop() {
	sum -= 1;
}
