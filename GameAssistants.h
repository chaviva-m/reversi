/*
 * GameAssistants.h
 *
 * Author: djoffe
 * Dana Joffe
 * ID 312129240
 */

#ifndef GAMEASSISTANTS_H_
#define GAMEASSISTANTS_H_

#include "SharedCode.h"

/*
 * Observer-Listener Design Pattern:
 * each class that will implement this pure virtual class could be
 * notified when a cell on the board is flipped.
 */
class FlipListener {
public:
	/*
	 * virtual destructor.
	 */
	virtual ~FlipListener();
	/*
	 * inform this object on a flip occurrence.
	 * @param from: the player type that is being flipped.
	 * @param to: the player type that is now.
	 */
	virtual void flipOccured(const PlayerEnum from, const PlayerEnum to)=0;
};

/*
 * pure virtual class.
 * can count things.
 */
class Counter {
public:
	/*
	 * virtual destructor.
	 */
	virtual ~Counter();
	/*
	 * @return: total countings. sum, amount.
	 */
	virtual int total()=0;
	/*
	 * increase the counter.
	 */
	virtual void raise()=0;
	/*
	 * decrease the counter.
	 */
	virtual void drop()=0;
private:

};

/*
 * a counter that counts how many cells contains a specific player.
 * implementation of Listener-Observer Design Patterns.
 */
class FlipCounter: public Counter, public FlipListener {
public:
	/*
	 * constructor.
	 * @param player: a player type.
	 */
	FlipCounter(PlayerEnum player);
	/*
	 * destructor.
	 */
	~FlipCounter();
	/*
	* inform this object on a flip occurrence.
	* @param from: the player type that is being flipped.
	* @param to: the player type that is now.
	*/
	virtual void flipOccured(const PlayerEnum from, const PlayerEnum to);
	/*
	 * @return: total countings. sum, amount.
	 */
	virtual int total();
	/*
	 * increase the counter.
	 */
	virtual void raise();
	/*
	 * decrease the counter.
	 */
	virtual void drop();
private:
	PlayerEnum player;
	int sum;
};



#endif /* GAMEASSISTANTS_H_ */
