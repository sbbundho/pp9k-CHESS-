#include <string>
#include <iostream>
#include <sstream>

#include "humanplayer.h"
#include "gamepiece.h"
using namespace std;

HumanPlayer::HumanPlayer(Board *board, char team) : Player(board, team) {}

void getCoords(string posn, int *a, int *b) {
	int x = 0;
	int y = 0;
	char c = 0;
	istringstream iss(posn);

	iss >> c >> y;
	x = c - 'a';
	y = y - 1;
	*a = x;
	*b = y;
}

void HumanPlayer::getMove() {
	string command;
	string posn1;
	string posn2;
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;

	cin >> posn1 >> posn2;

	getCoords(posn1, &x1, &y1);
	getCoords(posn2, &x2, &y2);

	if (board->getPieceAt(x1,y1) == NULL) {
		char c = x1 + 'a';
		cout << "No piece to move at " << c << y1 + 1 << endl;
		cout << "Make another move." << endl;

		if(cin >> command) getMove();
	} else {
		if (board->getPieceAt(x1, y1)->getTeam() != team) {
			cout << "Player's team is " << team << endl;
			cout << "Piece's team is " << board->getPieceAt(x1, y1)->getTeam() << endl;
			cout << "Cannot move enemy opponent's piece.  Make another move." << endl;

			if(cin >> command) getMove();
		} else if (! board->getPieceAt(x1,y1)->move(x2, y2)) {
			cout << "Invalid move. Make another move." << endl;

			if(cin >> command) getMove();
		}
	}
	
}

HumanPlayer::~HumanPlayer() {}




