#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include <string>

class Player;
class GamePiece;
class Controller;

class Board {

	public:
		static const int BOARDSIZE = 8;
		static const int NUMPIECES = 16;
		Board(Controller *ctrl);
		int loadBoard(std::string filename);

		void update(int x1, int y1, int x2, int y2);
		void updateSingle(int x, int y, char c);
		void init(char team, int x, int y, std::string piece);

		~Board();

		bool withinBounds(int x, int y);
		bool validBoard();

		void setPreviousPlayedPiece(GamePiece *p);
		GamePiece *getPreviousPlayedPiece();

		GamePiece *getPieceAt(int x, int y);
		bool isEmptyAt(int x, int y);

		void resetBoard();
		void capturePiece(int x, int y);
		bool isOtherPlayerInCheck(char team);
		bool isWhiteInCheck();
		bool isBlackInCheck();

		bool canCaptureWhiteAttackingPiece();
		bool canCaptureBlackAttackingPiece();
		bool canProtectWhiteKing();
		bool canProtectBlackKing();
		bool canWhiteKingEscapeCheck();
		bool canBlackKingEscapeCheck();
		bool isWhiteinCheckMate();
		bool isBlackinCheckMate();
		bool isCheckmate();

		void pawnPromotion(char team, int x, int y, std::string promotion);

		GamePiece *getColouredPiece(char team, int i);
		void setPlayer1(Player *p);
		void setPlayer2(Player *p);

	private:
		GamePiece *gp[BOARDSIZE][BOARDSIZE];

		GamePiece *whitePieces[NUMPIECES];
		GamePiece *blackPieces[NUMPIECES];

		GamePiece *previousPlayedPiece;
		Controller *controller;

		Player *player1;
		Player *player2;

		int kingCount; // Integer indicating how many King objects were created
		// Booleans indicating whether the player (white/black) is in check
		bool whiteCheck;
		bool blackCheck;
		bool canProtectBKing;
		bool canProtectWKing;
		bool canCaptureWhite;
		bool canCaptureBlack;


		void clearBoard();
		void addToList(GamePiece *gamePiece, int i);

		void findAndNullifyColouredPiece(int x, int y);
};

#endif




