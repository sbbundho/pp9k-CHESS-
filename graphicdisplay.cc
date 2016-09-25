#include "graphicdisplay.h"
#include "textdisplay.h"
#include <iostream>
#include <string>

using namespace std;

const double WINDOW_SIZE = 500;
const double SQUARE_SIZE = WINDOW_SIZE / 8;
const double X_OFFSET = WINDOW_SIZE / 16 - 4;
const double Y_OFFSET = WINDOW_SIZE / 16 + 2;
const int COLOUR = Xwindow::Blue;

void GraphicDisplay::whiteBlackAlternatingFill(int x, int y) {
	int divisor = SQUARE_SIZE * 2;
	if (x % divisor == 0) {
		if (y % divisor == 0) {
			xwindow->fillRectangle(x, y, SQUARE_SIZE, SQUARE_SIZE, Xwindow::White);
		} else {
			xwindow->fillRectangle(x, y, SQUARE_SIZE, SQUARE_SIZE, Xwindow::Black);
		}
	} else {
		if (y % divisor == 0) {
			xwindow->fillRectangle(x, y, SQUARE_SIZE, SQUARE_SIZE, Xwindow::Black);
		} else {
			xwindow->fillRectangle(x, y, SQUARE_SIZE, SQUARE_SIZE, Xwindow::White);
		}
	}
}

GraphicDisplay::GraphicDisplay(TextDisplay *textDisplay) {
	xwindow = new Xwindow();

	for (double x = 0; x < WINDOW_SIZE; x += SQUARE_SIZE) {
		for (double y = 0; y < WINDOW_SIZE; y += SQUARE_SIZE) {
			whiteBlackAlternatingFill(x, y);
			string s(1, textDisplay->getChar(x/SQUARE_SIZE, y/SQUARE_SIZE));
			if (s != "_") xwindow->drawBigString(x + X_OFFSET, y + Y_OFFSET, s, COLOUR);
		}
	}
}

void GraphicDisplay::update(int x1, int y1, char c1, int x2, int y2, char c2) {
	string s1(1, c1);
	string s2(1, c2);
	double x1Scaled = x1*SQUARE_SIZE;
	double y1Scaled = WINDOW_SIZE - SQUARE_SIZE - y1*SQUARE_SIZE;
	whiteBlackAlternatingFill(x1Scaled, y1Scaled);

	double x2Scaled = x2*SQUARE_SIZE;
	double y2Scaled = WINDOW_SIZE - SQUARE_SIZE - y2*SQUARE_SIZE;
	whiteBlackAlternatingFill(x2Scaled, y2Scaled);

	if (s1 != "_") xwindow->drawBigString(x1Scaled + X_OFFSET, y1Scaled + Y_OFFSET, s1, COLOUR);
	if (s2 != "_") xwindow->drawBigString(x2Scaled + X_OFFSET, y2Scaled + Y_OFFSET, s2, COLOUR);
}

void GraphicDisplay::updateSingle(int x, int y, char c) {
	string s(1, c);
	double xScaled = x*SQUARE_SIZE;
	double yScaled = WINDOW_SIZE - SQUARE_SIZE - y*SQUARE_SIZE;
	whiteBlackAlternatingFill(xScaled, yScaled);
	if (s != "_") xwindow->drawBigString(xScaled + X_OFFSET, yScaled + Y_OFFSET, s, COLOUR);
}

GraphicDisplay::~GraphicDisplay() {
	delete xwindow;
}

