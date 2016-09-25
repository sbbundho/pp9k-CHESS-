#include "computerone.h"
#include "gamepiece.h"
#include "board.h"

#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

#include <cstdlib>

using namespace std;

ComputerLevelOne::ComputerLevelOne(Board *board, char team) : Player(board, team) {
	for (int i = 0; i < NUMPIECES; i++) {
		this->pieces[i] = board->getColouredPiece(team, i);
	}
}

void ComputerLevelOne::addMoveToVector(int x, int y) {
	move m;
	m.x = x;
	m.y = y;
	moves.push_back(m);
}

void ComputerLevelOne::nullifyPiece(int i) {
	if (i >= 0 && i < NUMPIECES) pieces[i] = NULL;
}

bool ComputerLevelOne::canMove(Pawn *pawn) {
	int x = pawn->getX();
	int y = pawn->getY();

	if (pawn->isValidMove(x, y+1)) addMoveToVector(x, y+1);
	if (pawn->isValidMove(x, y+2)) addMoveToVector(x, y+2);
	if (pawn->isValidMove(x, y-1)) addMoveToVector(x, y-1);
	if (pawn->isValidMove(x, y-2)) addMoveToVector(x, y-2);
	if (pawn->isValidMove(x+1, y+1)) addMoveToVector(x+1, y+1);
	if (pawn->isValidMove(x+1, y-1)) addMoveToVector(x+1, y-1);
	if (pawn->isValidMove(x-1, y+1)) addMoveToVector(x-1, y+1);
	if (pawn->isValidMove(x-1, y-1)) addMoveToVector(x-1, y-1);

	return (moves.size() > 0);
	
}

bool ComputerLevelOne::canMove(Rook *rook) {
	int x = rook->getX();
	int y = rook->getY();

	for (int i = 0; i < board->BOARDSIZE; i++) {
		if (rook->isValidMove(i, y)) addMoveToVector(i, y);
		if (rook->isValidMove(x, i)) addMoveToVector(x, i);
	}

	return (moves.size() > 0);
}

bool ComputerLevelOne::canMove(Knight *knight) {
	int x = knight->getX();
	int y = knight->getY();

	if (knight->isValidMove(x+1, y+2)) addMoveToVector(x+1, y+2);
	if (knight->isValidMove(x+1, y-2)) addMoveToVector(x+1, y-2);
	if (knight->isValidMove(x-1, y+2)) addMoveToVector(x-1, y+2);
	if (knight->isValidMove(x-1, y-2)) addMoveToVector(x-1, y-2);
	if (knight->isValidMove(x+2, y+1)) addMoveToVector(x+2, y+1);
	if (knight->isValidMove(x+2, y-1)) addMoveToVector(x+2, y-1);
	if (knight->isValidMove(x-2, y+1)) addMoveToVector(x-2, y+1);
	if (knight->isValidMove(x-2, y-1)) addMoveToVector(x-2, y-1);

	return (moves.size() > 0);
}

bool ComputerLevelOne::canMove(Bishop *bishop) {
	int x = bishop->getX();
	int y = bishop->getY();

	for (int i = -7; i < board->BOARDSIZE; i++) {
		if (bishop->isValidMove(x+i, y+i)) addMoveToVector(x+i, y+i);
		if (bishop->isValidMove(x+i, y-i)) addMoveToVector(x+i, y-i);
	}

	return (moves.size() > 0);
}

bool ComputerLevelOne::canMove(Queen *queen) {
	int x = queen->getX();
	int y = queen->getY();

	for (int i = -7; i < board->BOARDSIZE; i++) {
		if (queen->isValidMove(x+i, y+i)) addMoveToVector(x+i, y+i);
		if (queen->isValidMove(x+i, y-i)) addMoveToVector(x+i, y-i);
	}

	for (int i = 0; i < board->BOARDSIZE; i++) {
		if (queen->isValidMove(i, y)) addMoveToVector(i, y);
		if (queen->isValidMove(x, i)) addMoveToVector(x, i);
	}

	return (moves.size() > 0);
}

bool ComputerLevelOne::canMove(King *king) {
	int x = king->getX();
	int y = king->getY();

	if (king->isValidMove(x+2, y)) addMoveToVector(x+2, y);
	if (king->isValidMove(x-2, y)) addMoveToVector(x-2, y);

	if (king->isValidMove(x+1, y)) addMoveToVector(x+1, y);
	if (king->isValidMove(x+1, y+1)) addMoveToVector(x+1, y+1);
	if (king->isValidMove(x-1, y)) addMoveToVector(x-1, y);
	if (king->isValidMove(x-1, y+1)) addMoveToVector(x-1, y+1);
	if (king->isValidMove(x, y+1)) addMoveToVector(x, y+1);
	if (king->isValidMove(x, y-1)) addMoveToVector(x, y-1);
	if (king->isValidMove(x+1, y-1)) addMoveToVector(x+1, y-1);
	if (king->isValidMove(x-1, y-1)) addMoveToVector(x-1, y-1);

	return (moves.size() > 0);

}

void ComputerLevelOne::makeRandomMove(GamePiece *gamePiece) {
	move m = moves.at(rand() % moves.size());
	gamePiece->move(m.x, m.y);
}

void ComputerLevelOne::getMove() {
	srand(time(NULL));
	int i = 0;

	while (true) {
		i = rand() % NUMPIECES;
		if (pieces[i] == NULL) continue;

		Pawn *p = dynamic_cast<Pawn*>(pieces[i]);
		if (p != NULL) {
			if (canMove(p)) {
				makeRandomMove(p);
				moves.clear();
				break;
			}
		}

		Rook *r = dynamic_cast<Rook*>(pieces[i]);
		if (r != NULL) {
			if (canMove(r)) {
				makeRandomMove(r);
				moves.clear();
				break;
			}
		}

		Knight *n = dynamic_cast<Knight*>(pieces[i]);
		if (n != NULL) {
			if (canMove(n)) {
				makeRandomMove(n);
				moves.clear();
				break;
			}
		}

		Bishop *b = dynamic_cast<Bishop*>(pieces[i]);
		if (b != NULL) {
			if (canMove(b)) {
				makeRandomMove(b);
				moves.clear();
				break;
			}
		}

		Queen *q = dynamic_cast<Queen*>(pieces[i]);
		if (q != NULL) {
			if (canMove(q)) {
				makeRandomMove(q);
				moves.clear();
				break;
			}
		}

		King *k = dynamic_cast<King*>(pieces[i]);
		if (k != NULL) {
			if (canMove(k)) {
				makeRandomMove(k);
				moves.clear();
				break;
			}
		}
	}
}

ComputerLevelOne::~ComputerLevelOne() {}

