#include "knight.h"

using namespace std;

Knight::Knight(char team, int x, int y, Board *board)
	: GamePiece(team, x, y, board) {
}

bool Knight::isValidMove(int newx, int newy) {
	return (board->withinBounds(newx, newy) && genericIsValidMove(newx, newy) &&
		((x + 1 == newx && y + 2 == newy) || (x + 1 == newx && y - 2 == newy) ||
		(x - 1 == newx && y + 2 == newy) || (x - 1 == newx && y - 2 == newy) ||
		(x + 2 == newx && y + 1 == newy) || (x + 2 == newx && y - 1 == newy) ||
		(x - 2 == newx && y + 1 == newy) || (x - 2 == newx && y - 1 == newy)));
}

Knight::~Knight() {}


