#ifndef __GRAPHICDISPLAY_H__
#define __GRAPHICDISPLAY_H__

#include "view.h"
#include "window.h"

class TextDisplay;

class GraphicDisplay{
	Xwindow *xwindow;

	void whiteBlackAlternatingFill(int x, int y);

	public:
		GraphicDisplay(TextDisplay *textDisplay);
		void update(int x1, int y1, char c1, int x2, int y2, char c2);
		void updateSingle(int x, int y, char c);
		~GraphicDisplay();

};
#endif

