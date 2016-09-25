#ifndef __PAWN_H__
#define __PAWN_H__

#include "gamepiece.h"

class Pawn : public GamePiece {
	bool isEnPassantMove(int newx, int newy);
	
	public:
		Pawn(char team, int x, int y, Board *board);
		bool isValidMove(int newx, int newy);
		~Pawn();

};
#endif


