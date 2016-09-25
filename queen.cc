#include <cmath>
#include "queen.h"

using namespace std;

Queen::Queen(char team, int x, int y, Board *board)
	: GamePiece(team, x, y, board) {
}

bool Queen::isValidMove(int newx, int newy) {
	if (!board->withinBounds(newx, newy)) return false;

	int dx = x - newx;
	int dy = y - newy;

	if (dx == 0 || dy == 0) {
		return (genericIsValidMove(newx, newy) && hasClearPath(x, y, newx, newy));
	} else {
		return (abs(dx) == abs(dy) && genericIsValidMove(newx, newy) &&
			hasClearPath(x, y, newx, newy));
	}
}

Queen::~Queen() {}



