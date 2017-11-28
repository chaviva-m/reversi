/*
 * Disk.h
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#ifndef DISK_H_
#define DISK_H_

#include <iostream>
#include <string>
#include "color.h"

/**
 * disk piece for game. has color.
 */
class Disk {
public:
  /**
   * constructs disk with color
   * input: Color color
   * output: void
   */
	Disk(Color color);
  /**
   * access color of disk
   * input: void
   * output: Color of disk
   */
	Color getColor() const;
  /**
   * switch color of disk
   * input: void
   * output: void
   */
	void flipDisk();

	/**
	 * return true if disks are equal.
	 */
	bool operator ==(const Disk& disk) const;
  /**
   * return true if disks are unequal.
   */
	bool operator !=(const Disk& disk) const;

private:
	Color color_;
};

#endif /* DISK_H_ */
