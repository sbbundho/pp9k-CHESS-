#include <cmath>
#include "bishop.h"

using namespace std;

Bishop::Bishop(char team, int x, int y, Board *board)
	: GamePiece(team, x, y, board) {
}

bool Bishop::isValidMove(int newx, int newy) {
	int dx = x - newx;
	int dy = y - newy;

	return (abs(dx) == abs(dy) && board->withinBounds(newx, newy) && 
		genericIsValidMove(newx, newy) && hasClearPath(x, y, newx, newy));
}

Bishop::~Bishop() {}


