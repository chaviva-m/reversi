/*
 * Color.h
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
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
