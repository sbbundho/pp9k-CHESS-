#include "textdisplay.h"
#include <iostream>

using namespace std;

char spaceOrUnderscore(int x, int y) {
	if (x % 2 == 0) {
		if (y % 2 == 0) return '_';
		else return ' ';
	} else {
		if (y % 2 == 0) return ' ';
		else return '_';
	}
}

TextDisplay::TextDisplay() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (j == 0) {
				if (i == 0 || i == BOARD_SIZE - 1) display[i][j] = 'r';
				else if (i == 1 || i == BOARD_SIZE - 2) display[i][j] = 'n';
				else if (i == 2 || i == BOARD_SIZE - 3) display[i][j] = 'b';
				else if (i == 3) display[i][j] = 'q';
				else display[i][j] = 'k';
			} else if (j == 1) {
				display[i][j] = 'p';
 			} else if (j == BOARD_SIZE - 2) {
 				display[i][j] = 'P';
 			} else if (j == BOARD_SIZE - 1) {
 				if (i == 0 || i == BOARD_SIZE - 1) display[i][j] = 'R';
				else if (i == 1 || i == BOARD_SIZE - 2) display[i][j] = 'N';
				else if (i == 2 || i == BOARD_SIZE - 3) display[i][j] = 'B';
				else if (i == 3) display[i][j] = 'Q';
				else display[i][j] = 'K';
 			} else {
 				display[i][j] = spaceOrUnderscore(i, j);
 			}
		}
	}
}

/*
void TextDisplay::updateSingle(int x, int y, char c) {
	if (c == '_') display[BOARD_SIZE - 1 - y][x] = spaceOrUnderscore(BOARD_SIZE - 1 - y, x);
	display[BOARD_SIZE - 1 - y][x] = c;
}
*/

void TextDisplay::update(int x1, int y1, int x2, int y2) {
	display[x2][y2] = display[x1][y1];
	display[x1][y1] = spaceOrUnderscore(x1, y1);

	print(cout);
}

void TextDisplay::updateSingle(int x, int y, char c) {
	if (c == '_') display[x][y] = spaceOrUnderscore(x, y);
	else display[x][y] = c;
}

char TextDisplay::getChar(int x, int y) {
	if (x < BOARD_SIZE && x >= 0 && y < BOARD_SIZE && y >= 0) return display[x][y];
	else return '_';
}

void TextDisplay::print(ostream &out) {
	for (int i = BOARD_SIZE - 1; i >= 0; i--) {
		out << i + 1 << "  ";
		for (int j = 0; j < BOARD_SIZE; j++) {
			out << display[j][i];
		}
		out << endl;
	}
	out << endl;
	out << "   " << "abcdefgh" << endl;
}

TextDisplay::~TextDisplay() {}






