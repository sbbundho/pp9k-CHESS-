#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "gamepiece.h"

class Knight : public GamePiece {
	public:
		Knight(char team, int x, int y, Board *board);
		bool isValidMove(int newx, int newy);
		~Knight();

};
#endif

