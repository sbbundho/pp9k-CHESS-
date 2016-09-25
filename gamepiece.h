#ifndef __GAMEPIECE_H__
#define __GAMEPIECE_H__

#include "board.h"
#include "controller.h"

class GamePiece {	
	protected:
		char team;
		int x;
		int y;
		int movesPlayed;
		Board *board;
		bool genericIsValidMove(int newx, int newy);
		bool hasClearPath(int x1, int y1, int x2, int y2);

	public:
		GamePiece(char team, int x, int y, Board *board);
		virtual bool isValidMove(int newx, int newy) = 0;
		bool move(int newx, int newy);
		char getTeam();
		int getX();
		int getY();
		int getMovesPlayed();
		virtual ~GamePiece();

};
#endif


