/*
 * Printer.h
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#ifndef PRINTER_H_
#define PRINTER_H_

#include "Board.h"

/*
 * prints messages and reversi board to reversi's players.
 */
class Printer {
public:
    /*
     * virtual constructor (copying)
     * return: a pointer to a new printer.
     */
    virtual Printer* clone () const = 0;
    /*
     * the function prints a board.
     * input: board - a Reversi board.
     */
    virtual void printBoard(const Board& board) const =0;
    /*
     * the function prints a board.
     * input: message - a string message to print.
     * 		  loc - a location in which the message should be printed.
     */
    virtual void printMessage(const std::string& message,
        Point loc = Point(1,1)) const =0;
     /*
      * virtual destructor.
      */
      virtual ~Printer() {};
};

#endif /* PRINTER_H_ */
