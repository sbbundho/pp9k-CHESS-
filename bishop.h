#ifndef __BISHOP_H__
#define __BISHOP_H__

#include "gamepiece.h"

class Bishop : public GamePiece {
	public:
		Bishop(char team, int x, int y, Board *board);
		bool isValidMove(int newx, int newy);
		~Bishop();

};
#endif

