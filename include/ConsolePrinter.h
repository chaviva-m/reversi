/*
 * ConsolePrinter.h
 *
 * Author1: name & ID: Dana Joffe 312129240
 * Author2: name & ID: Chaviva Moshavi 322082892
 */

#ifndef CONSOLEPRINTER_H_
#define CONSOLEPRINTER_H_

#include "Printer.h"
#include <iostream>

class ConsolePrinter: public Printer {
public:
  /*
     * constructor.
     */
    ConsolePrinter();
    /*
    * virtual destructor.
    */
    virtual ~ConsolePrinter ();
    /*
     * virtual constructor (copying)
     * @return: a pointer to a new ConsolePrinter.
     */
    virtual ConsolePrinter* clone () const;
    /*
     * the function prints a board.
     * @param board: a Reversi board.
     */
    virtual void printBoard(const Board& board) const ;
    /*
    * the function prints a board.
    * @param message: a string message to print.
    * @param loc: a location in which the message should be printed.
     */
    virtual void printMessage(const std::string& message, Point loc = Point(1,1)) const;
};

#endif /* CONSOLEPRINTER_H_ */
