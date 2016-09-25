#ifndef __ROOK_H__
#define __ROOK_H__

#include "gamepiece.h"

class Rook : public GamePiece {
	public:
		Rook(char team, int x, int y, Board *board);
		bool isValidMove(int newx, int newy);
		~Rook();

};
#endif

