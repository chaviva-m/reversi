/*
 * Disk.h
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
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

private:
	Color color_;
};

#endif /* DISK_H_ */
