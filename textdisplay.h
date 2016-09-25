#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include "view.h"

class TextDisplay : public View {
	public:
		static const int BOARD_SIZE = 8;
		TextDisplay();
		void update(int x1, int y1, int x2, int y2);
		void updateSingle(int x, int y, char c);
		void print(std::ostream &out);
		char getChar(int x, int y);
		~TextDisplay();

	private:
		char display[BOARD_SIZE][BOARD_SIZE];

};
#endif



