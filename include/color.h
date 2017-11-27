/*
 * Color.h
 *
 * Author: Chaviva Moshavi
 * ID: 322082892
 */

#ifndef COLOR_H_
#define COLOR_H_

#include <iostream>

//colors of disks
enum Color {BLACK, WHITE, LAST_COLOR};

/**
 * output for enum Color
 */
std::ostream& operator <<(std::ostream &out, const Color &color);

#endif /* COLOR_H_ */
