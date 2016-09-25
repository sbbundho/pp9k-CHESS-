#include "king.h"

#include "rook.h"
#include "gamepiece.h"

using namespace std;

King::King(char team, int x, int y, Board *board) : GamePiece(team, x, y, board) {}

/*
This function completes Castling by moving the Rook and returns true, if valid
*/
bool King::isCastlingMove(int dx, int dy) {
	if (movesPlayed > 0 || dy != 0 || (dx != 2 && dx != -2)) {
		return false;
	}

	if (dx == 2 && hasClearPath(x, y, board->BOARDSIZE - 1, y)) {
		if (board->getPieceAt(board->BOARDSIZE -1, y) != NULL) {
			Rook *rook = dynamic_cast<Rook*>(board->getPieceAt(board->BOARDSIZE -1, y));

			if (rook != NULL && rook->isValidMove(x + 1, y)) {
				rook->move(x + 1, y);
				return true;
			}
		}
	} else if (dx == -2 && hasClearPath(x, y, 0, y)) {
		if (board->getPieceAt(0, y) != NULL) {
			Rook *rook = dynamic_cast<Rook*>(board->getPieceAt(0, y));

			if (rook != NULL && rook->isValidMove(x - 1, y)) {
				rook->move(x - 1, y);
				return true;
			}
		}
	}
	return false;

}

bool King::isValidMove(int newx, int newy) {
	if (!board->withinBounds(newx, newy)) return false;

	int dx = newx - x;
	int dy = newy - y;

	return (isCastlingMove(dx, dy) || ((dx <= 1 && dx >= -1 && dy <= 1 && dy >= -1) &&
			genericIsValidMove(newx, newy)));
}

King::~King() {}


