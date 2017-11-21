/*
 * Printer.h
 *
 *  Created on: Nov 20, 2017
 *      Author: chaviva
 */

#ifndef PRINTER_H_
#define PRINTER_H_

#include "Board.h"

class Printer {
public:
    /*
     * virtual constructor (copying)
     * @return: a pointer to a new printer.
     */
    virtual Printer* clone () const = 0;
    /*
     * the function prints a board.
     * @param board: a Reversi board.
     */
    virtual void printBoard(const Board& board) const =0;
    /*
     * the function prints a board.
     * @param message: a string message to print.
     * @param loc: a location in which the message should be printed.
     */
    virtual void printMessage(const std::string& message,
        Point loc = Point(1,1)) const =0;
    /*
       * virtual destructor.
       */
      virtual ~Printer() {};
};

#endif /* PRINTER_H_ */
