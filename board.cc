#include <iostream>
#include <fstream>
#include <string>

#include "board.h"
#include "gamepiece.h"
#include "controller.h"
#include "player.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "computerone.h"

using namespace std;

void Board::clearBoard() {
	for (int i = 0; i < NUMPIECES; i++) {
		whitePieces[i] = NULL;
		blackPieces[i] = NULL;
	}

	for (int i=0; i<BOARDSIZE; i++) {
		for (int j=0; j<BOARDSIZE; j++) {
			delete gp[i][j];
		}
	}
}

Board::Board(Controller *ctrl) {
	this->controller = ctrl;

	previousPlayedPiece = NULL;

	player1 = NULL;
	player2 = NULL;

	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
			gp[i][j] = NULL;
		}
	}

	for (int i = 0; i < NUMPIECES; i++) {
		whitePieces[i] = NULL;
		blackPieces[i] = NULL;
	}

	kingCount = 0;

	resetBoard();
}

Board::~Board() {
	clearBoard();
}

void Board::setPlayer1(Player *p) {
	player1 = p;
}

void Board::setPlayer2(Player *p) {
	player2 = p;
}

bool Board::withinBounds(int x, int y) {
	if ((x >= 0) && (x < BOARDSIZE) && (y >= 0) && (y < BOARDSIZE)) return true;
	else return false;
}

void Board::update(int x1, int y1, int x2, int y2) {
	isOtherPlayerInCheck(gp[x1][y1]->getTeam());
	gp[x2][y2] = gp[x1][y1];
	gp[x1][y1] = NULL;

	controller->updateView(x1, y1, x2, y2);
}

void Board::updateSingle(int x, int y, char c) {
	controller->updateSinglePiece(x, y, c);
}


void Board::findAndNullifyColouredPiece(int x, int y) {
	// White piece
	if (gp[x][y]->getTeam() == 'W') {
		for (int i = 0; i < NUMPIECES; i++) {
			if (whitePieces[i] == gp[x][y]) {
				ComputerLevelOne *cp = dynamic_cast<ComputerLevelOne*>(player2);
				if (cp != NULL) cp->nullifyPiece(i);
				whitePieces[i] = NULL;
				break;
			}
		}
	// Black piece
	} else {
		for (int i = 0; i < NUMPIECES; i++) {
			if (blackPieces[i] == gp[x][y]) {
				ComputerLevelOne *cp = dynamic_cast<ComputerLevelOne*>(player1);
				if (cp != NULL) cp->nullifyPiece(i);
				blackPieces[i] = NULL;
				break;
			}
		}
	}
}

void Board::capturePiece(int x, int y) {
	if (gp[x][y] == NULL) return;
	findAndNullifyColouredPiece(x, y);

	delete gp[x][y];
	gp[x][y] = NULL;
	updateSingle(x, y, '_');
}

void Board::pawnPromotion(char team, int x, int y, string promotion) {
	if (!withinBounds(x, y)) return;

	Pawn *p = dynamic_cast<Pawn*>(gp[x][y]);
	if (p != NULL && (y == 0 || y == BOARDSIZE - 1)) {
		findAndNullifyColouredPiece(x, y);
		init(team, x, y, promotion);
	}
}

void Board::addToList(GamePiece *gamePiece, int i) {
	char team = gamePiece->getTeam();
	// cout << "adding to list...i = " << i << " team = " << team << endl;

	for (int idx = i; idx < NUMPIECES; idx++) {
		// White piece
		if (team == 'W') {
			if (whitePieces[idx] == NULL) {
				// cout << "putting it in idx=" << idx << endl;
				whitePieces[idx] = gamePiece;
				break;
			}
		// Black piece
		} else {
			if (blackPieces[idx] == NULL) {
				// cout << "putting it in idx=" << idx << endl;
				blackPieces[idx] = gamePiece;
				break;
			}
		}
	}

}

bool Board::isOtherPlayerInCheck(char team) {
	if (team == 'W') {
		GamePiece *enemyKing = blackPieces[NUMPIECES - 1];

		// NULL King
		if (enemyKing == NULL) return false;

		int x = enemyKing->getX();
		int y = enemyKing->getY();

		for (int i = 0; i < NUMPIECES; i++) {
			
			if (whitePieces[i] == NULL) continue;
			if (whitePieces[i]->isValidMove(x, y)) {
				cout << "Black is in check." << endl;
				blackCheck = true;
			
				return true;	
			}
		}
		return false;
	} else {
		GamePiece *enemyKing = whitePieces[NUMPIECES - 1];

		// NULL King
		if (enemyKing == NULL) return false;

		int x = enemyKing->getX();
		int y = enemyKing->getY();

		for (int i = 0; i < NUMPIECES; i++) {
			if (blackPieces[i] == NULL) continue;
			if (blackPieces[i]->isValidMove(x, y)) {
				cout << "White is in check." << endl;
				whiteCheck = true;
		
				return true;	
			}
		}
		return false;
	}
}

void Board::init(char team, int x, int y, string piece) {
	if (!withinBounds(x,y)) return;

	if (piece == "PAWN" || piece == "P" || piece == "p") {
		delete gp[x][y];
		gp[x][y] = new Pawn(team, x, y, this);
		addToList(gp[x][y], 0);
		updateSingle(x, y, team == 'W' ? 'P' : 'p');

		//cout << "initializing Pawn at x=" << x << ", y=" << y << endl;
	} else if (piece == "ROOK" || piece == "R" || piece == "r") {
		delete gp[x][y];
		gp[x][y] = new Rook(team, x, y, this);
		addToList(gp[x][y], 8);
		updateSingle(x, y, team == 'W' ? 'R' : 'r');

		//cout << "initializing Rook at x=" << x << ", y=" << y << endl;
	} else if (piece == "KNIGHT" || piece == "N" || piece == "n") {
		delete gp[x][y];
		gp[x][y] = new Knight(team, x, y, this);
		addToList(gp[x][y], 10);
		updateSingle(x, y, team == 'W' ? 'N' : 'n');

		//cout << "initializing Knight at x=" << x << ", y=" << y << endl;
	} else if (piece == "BISHOP" || piece == "B" || piece == "b") {
		delete gp[x][y];
		gp[x][y] = new Bishop(team, x, y, this);
		addToList(gp[x][y], 12);
		updateSingle(x, y, team == 'W' ? 'B' : 'b');

		//cout << "initializing Bishop at x=" << x << ", y=" << y << endl;
	} else if (piece == "QUEEN" || piece == "Q" || piece == "q") {
		delete gp[x][y];
		gp[x][y] = new Queen(team, x, y, this);
		addToList(gp[x][y], 14);
		updateSingle(x, y, team == 'W' ? 'Q' : 'q');

		//cout << "initializing Queen at x=" << x << ", y=" << y << endl;
	} else if (piece == "KING" || piece == "K" || piece == "k") {
		delete gp[x][y];
		gp[x][y] = new King(team, x, y, this);
		addToList(gp[x][y], 15);
		updateSingle(x, y, team == 'W' ? 'K' : 'k');
		kingCount++;

		//cout << "initializing King at x=" << x << ", y=" << y << endl;
	} else if (piece == "NOTHING") {
		capturePiece(x, y);
	}
}

void Board::resetBoard() {
	kingCount = 0;

	// cout << "making standard board..." << endl;
	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
			if (j == 0) {
				if (i == 0 || i == BOARDSIZE - 1) init('W', i, j, "ROOK");
				else if (i == 1 || i == BOARDSIZE - 2) init('W', i, j, "KNIGHT");
				else if (i == 2 || i == BOARDSIZE - 3) init('W', i, j, "BISHOP");
				else if (i == 3) init('W', i, j, "QUEEN");
				else init('W', i, j, "KING");

			} else if (j == 1) {
				init('W', i, j, "PAWN");
			} else if (j == BOARDSIZE - 2) {
				init('B', i, j, "PAWN");
			} else if (j == BOARDSIZE - 1) {
				if (i == 0 || i == BOARDSIZE - 1) init('B', i, j, "ROOK");
				else if (i == 1 || i == BOARDSIZE - 2) init('B', i, j, "KNIGHT");
				else if (i == 2 || i == BOARDSIZE - 3) init('B', i, j, "BISHOP");
				else if (i == 3) init('B', i, j, "QUEEN");
				else init('B', i, j, "KING");

			} else {
				gp[i][j] = NULL;
			}
		}
	}
	 // cout << "done making board..." << endl;
}

int Board::loadBoard(string filename) {
	cout << "loading board from " << filename << " ..." << endl;

	ifstream infile(filename.c_str());
	string line;
	char c;

	// First 8 lines are board configuration.
	for (int i = 7; i >= 0; i--) {
		getline(infile, line);
		istringstream iss(line);

		for (int j = 0; j < 8; j++) {
			iss >> c;
			if (c == '_') {
				capturePiece(j, i);
				updateSingle(j, i, '_');
			}

			string s(1, c);
			init(c > 'a' ? 'B' : 'W', j, i, s);
		}
	}

	// Last line is a single character denoting the player to move next
	getline(infile, line);
	istringstream iss(line);
	iss >> c;
	if (c == 'B' || c == 'b') return 0;
	else return 1;
}

void Board::setPreviousPlayedPiece(GamePiece *p) {
	previousPlayedPiece = p;
}

GamePiece *Board::getPreviousPlayedPiece() {
	return previousPlayedPiece;
}

GamePiece *Board::getPieceAt(int x, int y) {
	if (withinBounds(x, y) && !(isEmptyAt(x,y))) {
		return gp[x][y];
	}
	else return NULL;
}

bool Board::isEmptyAt(int x, int y) {
	if (withinBounds(x, y) && gp[x][y] != NULL) {
		return false;
	}
	else return true;
}

bool Board::validBoard() {
	// Assume valid board at first.
	bool isValid = true;

	// Check for two Kings in total
	if (kingCount != 2) {
		cout << "There must be exactly one White and Black king." << endl;
		isValid = false;
	}

	// Check that there is one White and one Black King
	if (whitePieces[NUMPIECES - 1] == NULL) {
		cout << "There must be exactly one White King." << endl;
		isValid = false;
	}

	if (blackPieces[NUMPIECES - 1] == NULL) {
		cout << "There must be exactly one Black King." << endl;
		isValid = false;
	}

	// Check that no pawns are on the last row of either side of the board
	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j+= 7) {
			Pawn *p = dynamic_cast<Pawn*>(gp[i][j]);
			if (p != NULL) {
				cout << "Invalid Pawn at " << i << ", " << j << endl;
				isValid = false;
			}
		}
	}

	// Check that neither King is in check
	cout << "checking if start state is in check..." << endl;
	if (isOtherPlayerInCheck('W')) isValid = false;
	if (isOtherPlayerInCheck('B')) isValid = false;

	// cout << "done checking..." << endl;

	return isValid;
}

bool Board::isWhiteInCheck() {
	return whiteCheck;
}

bool Board::isBlackInCheck() {
	return blackCheck;
}

bool Board::canCaptureBlackAttackingPiece() {
	GamePiece *whiteKing = whitePieces[NUMPIECES - 1];
	int kingX = whiteKing->getX();
	int kingY = whiteKing->getY();

	int numAttackingBlackPiece = 0;
	GamePiece *attackingBlackPiece = NULL;
	for (int i=0; i<NUMPIECES; i++) {
		if (blackPieces[i]->isValidMove(kingX, kingY)) {
			numAttackingBlackPiece++;
			attackingBlackPiece = blackPieces[i];
		}
		else continue;
	}

	if (numAttackingBlackPiece == 1) { 
		// checking if attacking piece can be captured
		int x = attackingBlackPiece->getX();
		int y = attackingBlackPiece->getY();
		for (int i=0; i<NUMPIECES; i++) {
			if (whitePieces[i]->isValidMove(x, y)) {
				attackingBlackPiece = NULL;
				numAttackingBlackPiece = 0;
				canCaptureBlack = true;
			}
			else continue;
		}
	}
	else canCaptureBlack = false;

	return canCaptureBlack;
}

bool Board::canCaptureWhiteAttackingPiece() {
	GamePiece *blackKing = blackPieces[NUMPIECES - 1];
	int kingX = blackKing->getX();
	int kingY = blackKing->getY();

	int numAttackingWhitePiece = 0;
	GamePiece *attackingWhitePiece = NULL;
	for (int i=0; i<NUMPIECES; i++) {
		if (whitePieces[i]->isValidMove(kingX, kingY)) {
			numAttackingWhitePiece++;
			attackingWhitePiece = whitePieces[i];
		}
		else continue;
	}
	
	if (numAttackingWhitePiece == 1) { 
		// checking if attacking piece can be captured
		int x = attackingWhitePiece->getX();
		int y = attackingWhitePiece->getY();
		for (int i=0; i<NUMPIECES; i++) {
			if (blackPieces[i]->isValidMove(x, y)) {
				attackingWhitePiece = NULL;
				numAttackingWhitePiece = 0;
				canCaptureWhite = true;
			}
			else continue;
		}
	}
	else canCaptureWhite = false;

	return canCaptureWhite;
}

bool Board::canProtectWhiteKing() {
	GamePiece *whiteKing = whitePieces[NUMPIECES - 1];
	int kingX = whiteKing->getX();
	int kingY = whiteKing->getY();

	// checking if attacking piece is a Knight
	GamePiece *blackKnight1 = blackPieces[10];
	GamePiece *blackKnight2 = blackPieces[11];
	if (blackKnight1 != NULL && blackKnight1->isValidMove(kingX, kingY)) {
		canProtectWKing = false;
	}
	else if (blackKnight2 != NULL && blackKnight2->isValidMove(kingX, kingY)) {
		return canProtectWKing = false;
	}

	// check if any other piece can block attacking piece's 
	// path to white king given it's not a knight
	else {
		int atX, atY;
		for (int i=0; i<NUMPIECES; i++) {
			if (blackPieces[i]->isValidMove(kingX, kingY)) {
				atX = blackPieces[i]->getX();
				atY = blackPieces[i]->getY();
			}
			else continue;
		}
		for (int i =0; i<NUMPIECES-2; i++) {
			for (int x=0; x<BOARDSIZE; x++) {
				for (int y=0; y<BOARDSIZE; y++) {
					if (whitePieces[i]->isValidMove(x, y) && (((x > kingX) && (x < atX) && 
						(y > kingY) && (y < atY)) || ((x > kingX) && (x < atX) && (y < kingY) 
						&& (y > atY)) || ((x < kingX) && (x > atX) && (y > kingY) && (y < atY)) 
						|| ((x < kingX) && (x > atX) && (y < kingY) && (y > atY)))) {
						canProtectWKing = true;
					}
					else canProtectWKing = false;
				}
			}
		}
	}
	return canProtectWKing;
}

bool Board::canProtectBlackKing() {
	GamePiece *blackKing = blackPieces[NUMPIECES - 1];
	int kingX = blackKing->getX();
	int kingY = blackKing->getY();

	// checking if attacking piece is a Knight
	GamePiece *whiteKnight1 = whitePieces[10];
	GamePiece *whiteKnight2 = whitePieces[11];
	if (whiteKnight1 != NULL && whiteKnight1->isValidMove(kingX, kingY)) {
		canProtectBKing = false;
	}
	else if (whiteKnight2 != NULL && whiteKnight2->isValidMove(kingX, kingY)) {
		canProtectBKing= false;
	}

	// check if any other piece can block attacking piece's 
	// path to black king given it's not a knight
	else {
		int atX, atY;
		for (int i=0; i<NUMPIECES; i++) {
			if (whitePieces[i]->isValidMove(kingX, kingY)) {
				atX = whitePieces[i]->getX();
				atY = whitePieces[i]->getY();
			}
			else continue;
		}
		for (int i =0; i<NUMPIECES-2; i++) {
			for (int x=0; x<BOARDSIZE; x++) {
				for (int y=0; y<BOARDSIZE; y++) {
					if (blackPieces[i]->isValidMove(x, y) && (((x >= kingX) && (x < atX) && 
						(y >= kingY) && (y < atY)) || ((x >= kingX) && (x < atX) && (y <= kingY) 
						&& (y > atY)) || ((x <= kingX) && (x > atX) && (y >= kingY) && (y < atY)) 
						|| ((x <= kingX) && (x > atX) && (y <= kingY) && (y > atY)))) {
						canProtectBKing = true;
					}
					else canProtectBKing = false;
				}
			}
		}
	}
	return canProtectBKing;
}


bool Board::canWhiteKingEscapeCheck() {
	GamePiece *whiteKing = whitePieces[NUMPIECES - 1];

	for (int x=0; x<BOARDSIZE; x++) {
		for (int y=0; y<BOARDSIZE; y++) {
			if (!(whiteKing->isValidMove(x, y))) continue;
			else {
				for (int i=0; i<NUMPIECES; i++) {
					if (blackPieces[i]->isValidMove(x, y)) return true;
				}
			}
		}
	}
	return false;
}

bool Board::canBlackKingEscapeCheck() {
	GamePiece *blackKing = blackPieces[NUMPIECES - 1];

	for (int x=0; x<BOARDSIZE; x++) {
		for (int y=0; y<BOARDSIZE; y++) {
			if (!(blackKing->isValidMove(x, y))) continue;
			else {
				for (int i=0; i<NUMPIECES; i++) {
					if (whitePieces[i]->isValidMove(x, y)) return true;
					else continue;
				}
			}
		}
	}
	return false;
}


bool Board::isWhiteinCheckMate() {
	if (whiteCheck) {
		if (canCaptureBlackAttackingPiece()) return false;
		else if (canWhiteKingEscapeCheck()) return false;
		else if (canProtectWhiteKing()) return false;
		else return true;
	}
	else return false; // if not in Check
}

bool Board::isBlackinCheckMate() {
	if (blackCheck) {
		if (canCaptureWhiteAttackingPiece()) return false;
		else if (canBlackKingEscapeCheck()) return false;
		else if (canProtectBlackKing()) return false;
		else return true;
	}
	else return false; // if not in Check
}

bool Board::isCheckmate() {
	return isBlackinCheckMate() || isWhiteinCheckMate();
}

GamePiece *Board::getColouredPiece(char team, int i) {
	if (i < 0 || i >= NUMPIECES) return NULL;
	if (team == 'W') {
		return whitePieces[i];
	} else {
		return blackPieces[i];
	}
}


