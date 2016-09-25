#include "rook.h"

using namespace std;

Rook::Rook(char team, int x, int y, Board *board)
	: GamePiece(team, x, y, board) {
}

bool Rook::isValidMove(int newx, int newy) {
	if (!board->withinBounds(newx, newy)) return false;
	int dx = x - newx;
	int dy = y - newy;

	return ((dx == 0 || dy == 0) && genericIsValidMove(newx, newy) &&
			hasClearPath(x, y, newx, newy));
}

Rook::~Rook() {}

