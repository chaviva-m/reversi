/*
 * Printers.h
 *
 * Author: djoffe
 * Dana Joffe
 * ID 312129240
 */
#ifndef PRINTERS_H_
#define PRINTERS_H_

#include "BoardRelated.h"

/*
 * pure virtual class for different Revrsi printers.
 */
class Printer {
public:
	/*
	 * virtual destructor.
	 */
	virtual ~Printer();
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
	virtual void printMessage(const string& message, Location loc = Location(1,1)) const =0;

};

/*
 * implementation of abstract class Print. this ConsolePrinter
 * prints everything to the console.
 */
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
	virtual void printMessage(const string& message, Location loc = Location(1,1)) const;
};

#endif /* PRINTERS_H_ */
