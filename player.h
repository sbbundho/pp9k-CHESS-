#ifndef __PLAYER_H__
#define __PLAYER_H__

struct move {
	int x;
	int y;
};

class Board;

class Player {
	protected:
		Board *board;
		char team;
		
	public:
		Player(Board *board, char team);
		virtual ~Player();

		virtual void getMove() = 0;
};
#endif



