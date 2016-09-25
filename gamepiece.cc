#include "gamepiece.h"

using namespace std;

GamePiece::GamePiece(char team, int x, int y, Board *board) {
	this->team = team;
	this->x = x;
	this->y = y;
	this->board = board;
	movesPlayed = 0;
}

/*
This function is a generic function that is to be used with the overridden
isValidMove functions of specific subclasses to determine if a move is valid
*/
bool GamePiece::genericIsValidMove(int newx, int newy) {
	return (board->isEmptyAt(newx, newy) || (!(board->isEmptyAt(newx, newy)) &&
	 board->getPieceAt(newx, newy) != NULL &&
	 board->getPieceAt(newx, newy)->getTeam() != team));
}

bool GamePiece::hasClearPath(int x1, int y1, int x2, int y2) {
	int xmin = (x1 < x2 ? x1 : x2);
	int xmax = (x1 > x2 ? x1 : x2);
	int ymin = (y1 < y2 ? y1 : y2);
	int ymax = (y1 > y2 ? y1 : y2);

	if (x1 == x2) {
		for (int i = ymin + 1; i < ymax; i++) {
			if (!board->isEmptyAt(x1, i)) return false;
		}
	} else if (y1 == y2) {
		for (int i = xmin + 1; i < xmax; i++) {
			if (!board->isEmptyAt(i, y1)) return false;
		}
	} else {
		if ((x1 > x2 && y1 > y2) || (x1 < x2 && y1 < y2)) {
			for (int i = xmin + 1, j = ymin + 1; i < xmax && j < ymax; i++, j++) {
				if (!board->isEmptyAt(i, j)) return false;
			}
		} else {
			for (int i = xmin + 1, j = ymax - 1; i < xmax && j > ymin; i++, j--) {
				if (!board->isEmptyAt(i, j)) return false;
			}
		}
	}
	// Exhausted all possibilities; must have a clear path.
	return true;
}

bool GamePiece::move(int newx, int newy) {
	if (isValidMove(newx, newy)) {
		if (!board->isEmptyAt(newx, newy)) {
			// Delete pointer to the piece at newx, newy and set to NULL
			board->capturePiece(newx, newy);
		}
		board->update(x, y, newx, newy);
		x = newx;
		y = newy;
		movesPlayed++;
		board->setPreviousPlayedPiece(this);

		return true;
	}
	else return false;
}

char GamePiece::getTeam() {
	return team;
}

int GamePiece::getX() {
	return x;
}

int GamePiece::getY() {
	return y;
}

int GamePiece::getMovesPlayed() {
	return movesPlayed;
}

GamePiece::~GamePiece() {}



