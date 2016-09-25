#ifndef __QUEEN_H__
#define __QUEEN_H__

#include "gamepiece.h"

class Queen : public GamePiece {
	public:
		Queen(char team, int x, int y, Board *board);
		bool isValidMove(int newx, int newy);
		~Queen();

};
#endif

