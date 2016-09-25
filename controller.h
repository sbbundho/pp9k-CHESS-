#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "textdisplay.h"
#include "board.h"

class GraphicDisplay;

class Controller {
	Board *board;
	TextDisplay *textDisplay;
	GraphicDisplay *graphicDisplay;
	Player *player1;
	Player *player2;
	int turn; // Integer to indicate which player's turn it is.

	std::string filename;

	void setupMode();

	public:
		Controller();
		Controller(std::string filename);
		void startGame();
		void updateView(int x1, int y1, int x2, int y2);
		void updateSinglePiece(int x, int y, char c);
		~Controller();

};
#endif


