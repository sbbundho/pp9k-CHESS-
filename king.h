#ifndef __KING_H__
#define __KING_H__

#include "gamepiece.h"

class King : public GamePiece {
	bool isCastlingMove(int dx, int dy);

	public:
		King(char team, int x, int y, Board *board);
		bool isValidMove(int newx, int newy);
		~King();

};
#endif


