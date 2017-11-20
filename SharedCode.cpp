/*
 * SharedCode.cpp
 *
 * Author: djoffe
 * Dana Joffe
 * ID 312129240
 */

#include "SharedCode.h"

ostream &operator <<(ostream &out, const PlayerEnum &c) {
	out << "";
	if (c == White) {
		out << 'O';

	} else if (c == Black) {
		out << 'X';
	} else {
		out << ' ';
	}
	return out;
}
string operator ++(const PlayerEnum &c) {
	string str = "";
	if (c == White) {
		str = 'O';
	} else if (c == Black) {
		str = 'X';
	} else {
		str = ' ';
	}
	return str;
}
string intToStr(int num) {
	string result;
	ostringstream convert;
	convert << num;
	result = convert.str();
	return result;
}

