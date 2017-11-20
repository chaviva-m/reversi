/*
 * SharedCode.h
 *
 * Author: djoffe
 * Dana Joffe
 * ID 312129240
 */

#ifndef SHAREDCODE_H_
#define SHAREDCODE_H_

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>

using namespace std;

/*
 * defines player type.
 */
enum PlayerEnum {White, Black, None};

/*
 * operator overloading to print the Enum PlayerEnum.
 */
ostream &operator <<(ostream &out, const PlayerEnum &c);
/*
 * operator overloading.
 * @return: string version of Enum PlayerEnum.
 */
string operator ++(const PlayerEnum &c);
/*
 * @param num: an integer.
 * @return: a string version of num.
 */
string intToStr(int num);
#endif /* SHAREDCODE_H_ */
