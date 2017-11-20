/*
 * Game.cpp
 *
 * Author: djoffe
 * Dana Joffe
 * ID 312129240
 */

#include "Game.h"

GameManager::GameManager(Board& board, GameLogic& log): board(board), logic(log) {}
void GameManager::makeAMove(Player* player, Printer& printer) {
	bool valid;
	valid = false;
	printer.printMessage("Your possible moves: ");
	set<Location> op = this->logic.getMoveOptions(player->getColor(), this->board);
	string st = "";
	for(set<Location>::iterator it=op.begin();it!=op.end();it++){
		st = st + it->toString() + " ";
	}
	printer.printMessage(st);
	printer.printMessage("\n\nPlease enter your move row,col: ");

	Location loc = player->decideOnAmove(this->board, op);
	printer.printMessage("\n");
	while (!valid) {
		if (!(this->logic.isMoveValid(loc, player->getColor(), this->board))) {

			printer.printMessage("your choice is not valid. please enter two"
					" separated number from the options above: \n");
			loc = player->decideOnAmove(this->board, op);
		} else {
			valid = true;
		}
	}
	this->board.flip(loc, player->getColor());
	printer.printMessage("Current Board:\n");
	printer.printBoard(this->board);
	printer.printMessage(++player->getColor() + " played " + loc.toString() + "\n\n");
}

Game::Game(int r, int c, GameLogic* logic, Printer* printer, Player* player1, Player* player2) {
	this->board = new Board(r, c);
	this->logic = logic;
	this->gameManager = new GameManager(*(this->board), *(this->logic));
	p1 = player1;
	p2 = player2;
	this->p1Counter = NULL;
	this->p2Counter = NULL;
	this->printer = printer;
}
Game::Game(const Game &oldGame) {
	this->board = new Board(*(oldGame.board));
	this->logic = oldGame.logic->clone();
	this->printer = oldGame.printer->clone();
	this->gameManager = new GameManager(*(oldGame.gameManager));
	this->p1 = oldGame.p1->clone();
	this->p2 = oldGame.p2->clone();
	this->p1Counter = new FlipCounter(*(oldGame.p1Counter));
	this->p2Counter = new FlipCounter(*(oldGame.p2Counter));
}
Game::~Game() {
	delete this->board;
	delete this->logic;
	delete this->gameManager;
	delete this->p1Counter;
	delete this->p2Counter;
	delete this->printer;
	delete this->p1;
	delete this->p2;
}
void Game::addPlayers(Player* p1, Player* p2) {
	this->p1 = p1;
	this->p2 = p2;
	this->p1Counter = new FlipCounter(p1->getColor());
	this->p2Counter = new FlipCounter(p2->getColor());
	this->board->addFlipListener(this->p1Counter);
	this->board->addFlipListener(this->p2Counter);
}
void Game::announceWinner() const {
	this->printer->printMessage("Score:\n" + ++p1->getColor() + ": " +
			intToStr(this->p1Counter->total()) +"\n");

	this->printer->printMessage(++p2->getColor() + ": " +
			intToStr(this->p2Counter->total()) +"\n");
	if (this->p1Counter->total() > this->p2Counter->total()) {
		this->printer->printMessage(++p1->getColor() + " is the winner!\n");
	} else if (this->p2Counter->total() > this->p1Counter->total()) {
		this->printer->printMessage(++p2->getColor() + " is the winner!\n");
	} else {
		this->printer->printMessage("It's a tie\n");
	}
 }
void Game::start() {
	if (this->p1 == NULL || this->p2 == NULL) {
		this->printer->printMessage("there are no players yet.");
		return;
	}
	bool p1GotMoves = true;
	bool p2GotMoves = true;
	this->printer->printMessage("Current Board:\n");
	this->printer->printBoard(*(this->board));
	while (p1GotMoves || p2GotMoves) {
		this->printer->printMessage(++p1->getColor() + ": It's your move.\n");
		p1GotMoves = this->logic->haveMoves(p1->getColor(), *(this->board));
		p2GotMoves = this->logic->haveMoves(p2->getColor(), *(this->board));
		string noMoves = "No possible moves. Play passes back to the other player."
				" Press any key to continue.";
		string gameOver = "No possible moves to either players. Game over."
				" Press any key to continue.";
		if (p1GotMoves) {
			this->gameManager->makeAMove(p1, *this->printer);
		} else {
			if (p2GotMoves) {
				this->printer->printMessage(noMoves + "\n");
				string dummy;
				getline(cin, dummy);
				this->printer->printBoard(*(this->board));
			} else {
				this->printer->printMessage(gameOver + "\n");
				string dummy;
				getline(cin, dummy);
				break;
			}
		}
		this->printer->printMessage(++p2->getColor() + ": It's your move.\n");
		if (p2GotMoves) {
			this->gameManager->makeAMove(p2, *this->printer);
		} else {
			if (p1GotMoves) {
				this->printer->printMessage(noMoves + "\n");
				string dummy;
				getline(cin, dummy);
				this->printer->printBoard(*(this->board));
			} else {
				this->printer->printMessage(gameOver + "\n");
				string dummy;
				getline(cin, dummy);
				break;
			}
		}
	}
	this->announceWinner();
}
