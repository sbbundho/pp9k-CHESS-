#include "pawn.h"

using namespace std;

Pawn::Pawn(char team, int x, int y, Board *board)
	: GamePiece(team, x, y, board) {
}

bool Pawn::isEnPassantMove(int newx, int newy) {
	if (board->isEmptyAt(newx, y) || !board->isEmptyAt(newx, newy)) return false;
	if (board->getPreviousPlayedPiece() == NULL) return false;

	// En passant move only works with enemy pawn piece
	Pawn *p = dynamic_cast<Pawn*>(board->getPreviousPlayedPiece());
	if (p == NULL) return false;

	if (p->getMovesPlayed() != 1) return false;

	if (p == board->getPieceAt(newx, y)) {
		board->capturePiece(newx, y);
		return true;
	} else {
		return false;
	}

}

bool Pawn::isValidMove(int newx, int newy) {
	if (!board->withinBounds(newx, newy)) return false;

	else if (board->isEmptyAt(newx, newy)) {
		if (team == 'W') {
			return ((x == newx && y + 1 == newy) || (x == newx && y == 1 &&
			y + 2 == newy && movesPlayed == 0 && hasClearPath(x, y, newx, newy))
			|| isEnPassantMove(newx, newy));
		}
		else { // team is B
			return ((x == newx && y - 1 == newy) || (x == newx && y + 2 == board->BOARDSIZE &&
			y - 2 == newy && movesPlayed == 0 && hasClearPath(x, y, newx, newy))
			|| isEnPassantMove(newx, newy));
		}
	} 
	else { // capturing move
		if (team == 'W') {
			return ((board->getPieceAt(newx, newy)->getTeam() != team) && 
			((x + 1 == newx && y + 1 == newy) || (x - 1 == newx && y + 1 == newy)));
		}
		else {
			return ((board->getPieceAt(newx, newy)->getTeam() != team) && 
			((x - 1 == newx && y - 1 == newy) || (x + 1 == newx && y - 1 == newy)));
		}
	}
}

Pawn::~Pawn() {}


