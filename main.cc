#include "controller.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc == 2) {
		string filename(argv[1]);
		Controller c = Controller(filename);
		c.startGame();
	} else {
		Controller c;
		c.startGame();
	}
}

