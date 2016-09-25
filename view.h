#ifndef __VIEW_H__
#define __VIEW_H__

#include <iostream>
#include <sstream>

class View {
	public:
		virtual void update(int x1, int y1, int x2, int y2) = 0;
		virtual void updateSingle(int x, int y, char c) = 0;
		virtual void print(std::ostream &out) = 0;
		virtual ~View() {}
};
#endif

