#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "player.h"
#include <vector>

class GamePiece;
class Board;
class Pawn;
class Rook;
class Knight;
class Bishop;
class Queen;
class King;

class ComputerLevelOne : public Player {
	static const int NUMPIECES = 16;
	GamePiece *pieces[NUMPIECES];
	std::vector<move> moves;

	bool canMove(Pawn *pawn);
	bool canMove(Rook *rook);
	bool canMove(Knight *knight);
	bool canMove(Bishop *bishop);
	bool canMove(Queen *queen);
	bool canMove(King *king);

	void makeRandomMove(GamePiece *gamePiece);
	void addMoveToVector(int x, int y);

	public:
		ComputerLevelOne(Board *board, char team);
		void getMove();
		void nullifyPiece(int i);
		~ComputerLevelOne();

};
#endif

