#ifndef __HUMANPLAYER_H__
#define __HUMANPLAYER_H__

#include "player.h"
#include "board.h"

class HumanPlayer : public Player {
	public:
		HumanPlayer(Board *board, char team);
		~HumanPlayer();

		void getMove();
};

#endif


