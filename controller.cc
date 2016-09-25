#include <string>
#include <iostream>
#include <sstream>

#include "controller.h"
#include "humanplayer.h"
#include "textdisplay.h"
#include "graphicdisplay.h"
#include "computerone.h"
#include "pawn.h"

using namespace std;

//CONVENTION: black = player 1;  white = player 2.

Controller::Controller() {
	textDisplay = NULL;
	graphicDisplay = NULL;

	board = NULL;
	player1 = NULL;
	player2 = NULL;
	filename = "";
}

Controller::Controller(string filename) {
	textDisplay = NULL;
	graphicDisplay = NULL;

	board = NULL;
	player1 = NULL;
	player2 = NULL;
	this->filename = filename;
}

void Controller::updateView(int x1, int y1, int x2, int y2) {
	textDisplay->update(x1, y1, x2, y2);
	graphicDisplay->update(x1,y1,textDisplay->getChar(x1,y1), x2,y2,textDisplay->getChar(x2,y2));
}

void Controller::updateSinglePiece(int x, int y, char c) {
	textDisplay->updateSingle(x, y, c);
	graphicDisplay->updateSingle(x, y, textDisplay->getChar(x, y));
}

// Function to determine the team (black or white) of a piece.
// Capital letter - > white;  lower case letter -> black.
char determineTeam(string s, char c) {
	// s will be a single character string.

	char team = s[0] - c;
	if (team == 0) return 'B';
	else return 'W';
}

void Controller::setupMode() {
	board->resetBoard();

	string input;
	string colour;
	string piece;
	string coord;

	do {
		while (cin >> input) {
			if (input == "done") break;
			else if (input == "+") {
				cin >> piece >> coord;

				istringstream iss(coord);
				char c;
				int y;
				iss >> c >> y;

				int x = c - 'a';
				y = y - 1;

				if (board->withinBounds(x,y)) {
					if (piece == "p" || piece == "P") {
						board->init(determineTeam(piece, 'p'), x, y, "PAWN");
					} else if (piece == "r" || piece == "R") {
						board->init(determineTeam(piece, 'r'), x, y, "ROOK");
					} else if (piece == "n" || piece == "N") {
						board->init(determineTeam(piece, 'n'), x, y, "KNIGHT");
					} else if (piece == "b" || piece == "B") {
						board->init(determineTeam(piece, 'b'), x, y, "BISHOP");
					} else if (piece == "q" || piece == "Q") {
						board->init(determineTeam(piece, 'q'), x, y, "QUEEN");
					} else if (piece == "k" || piece == "K") {
						board->init(determineTeam(piece, 'k'), x, y, "KING");
					}

					textDisplay->update(x, y, x, y);
				}

			} else if (input == "-") {
				cin >> coord;

				istringstream iss(coord);
				char c;
				int y;
				iss >> c >> y;

				int x = c - 'a';
				y = y - 1;

				if (board->withinBounds(x,y)) {
					board->init(0, x, y, "NOTHING");
					updateView(x, y, x, y);
					graphicDisplay->updateSingle(x, y, textDisplay->getChar(x,y));
				}

			} else if (input == "=") {
				cin >> colour;
				if (colour == "black" || colour == "Black" || colour == "b") {
					turn = 0;
				} else if (colour == "white" || colour == "White" || colour == "w") {
					turn = 1;
				}
			}
		}
	} while (!board->validBoard());

	textDisplay->print(cout);	
}

void Controller::startGame() {
	string command;
	string p1;
	string p2;
	bool playing;
	string playAgain = "y";

	double p1Score = 0;
	double p2Score = 0;
	do {
		if (playAgain != "y" && playAgain != "Y") break;

		while (cin >> command) {
			if (command == "game") {

				// Initializes the board to the standard start configuration
				delete board;
				delete textDisplay;
				delete graphicDisplay;

				textDisplay = new TextDisplay();
				graphicDisplay = new GraphicDisplay(textDisplay);
				board = new Board(this);

				// Initialize turn counter.
				// turn % 2 == 0 -> player 1's turn;  turn % 2 == 1 -> player 2
				turn = 1;

				delete player1;
				delete player2;

				cin >> p1 >> p2;

				if (p1 == "human") {
					player1 = new HumanPlayer(board, 'B');
				} else {
					if (p1[p1.length()-1] == '1') player1 = new ComputerLevelOne(board, 'B');

					// Incomplete computer player levels.
					// Should create ComputerLevelTwo, ComputerLevelThree, ComputerLevelFour
					// as appropriate, where each of which has different getMove schemes.
					else if (p1[p1.length()-1] == '2') player1 = new ComputerLevelOne(board, 'B');
					else if (p1[p1.length()-1] == '3') player1 = new ComputerLevelOne(board, 'B');
					else if (p1[p1.length()-1] == '4') player1 = new ComputerLevelOne(board, 'B');
					else cout << "Invalid - enter either human or computer[1-4]." << endl;
				}
				
				if (p2 == "human") {
					player2 = new HumanPlayer(board, 'W');
				} else {
					if (p2[p2.length()-1] == '1') player2 = new ComputerLevelOne(board, 'W');

					// Incomplete computer player levels.
					// Should create ComputerLevelTwo, ComputerLevelThree, ComputerLevelFour
					// as appropriate, where each of which has different getMove schemes.
					else if (p2[p2.length()-1] == '2') player2 = new ComputerLevelOne(board, 'W');
					else if (p2[p2.length()-1] == '3') player2 = new ComputerLevelOne(board, 'W');
					else if (p2[p2.length()-1] == '4') player2 = new ComputerLevelOne(board, 'W');
					else cout << "Invalid - enter either human or computer[1-4]." << endl;
				}

				board->setPlayer1(player1);
				board->setPlayer2(player2);

				if (filename != "") {
					turn = board->loadBoard(filename);
					filename = "";
				}

				textDisplay->print(cout);

			} else if (command == "resign") {
				if (board == NULL || player1 == NULL || player2 == NULL) {
					cout << "No game is in progress; enter game command to start a game" << endl;
				} else {
					if (turn % 2 == 0) {
						cout << "Black resigns.  White wins!" << endl;
						p2Score++;
					} else {
						cout << "White resigns.  Black wins!" << endl;
						p1Score++;
					}

					delete board;
					board = NULL;

					playing = false;
					break;
				}

			} else if (command == "move") {
				if (board == NULL || player1 == NULL || player2 == NULL) {
					cout << "No game is in progress; enter game command to start a game" << endl;
				} else {

					playing = true;
					if (turn % 2 == 0) {
	                    player1->getMove();
	                    if (board->isOtherPlayerInCheck('B')) {
	                            cout << "Black is in check" << endl;
	                    }
	                    else if (board->isOtherPlayerInCheck('W')) {
	                            p1Score+= 0.5;
                                p2Score+= 0.5;
                                cout << "White is in check - Stalemate" << endl;
                                cout << "Match is a draw" << endl;
                                cout << "Score of this round:" << endl;
                                cout << "White: " << p2Score << endl;
                                cout << "Black: " << p1Score << endl;
                                break;
                        }
                    }
                    else {
                            player2->getMove();
                            if (board->isOtherPlayerInCheck('W')) {
                                    cout << "White is in check" << endl;
                            }
                            else if (board->isOtherPlayerInCheck('B')) {
                                    p1Score+= 0.5;
                                    p2Score+= 0.5;
                                    cout << "Black is in check - Stalemate" << endl;
                                    cout << "Match is a draw" << endl;
                                    cout << "Score of this round:" << endl;
                                    cout << "White: " << p2Score << endl;
                                    cout << "Black: " << p1Score << endl;
                                    break;
                            }
                    }

					/*
					if (board->isCheckmate()) {
						if (turn % 2 == 0) {
							cout << "Player 1 wins!" << endl;
							p1Score++;
						} else {
							cout << "Player 2 wins!" << endl;
							p2Score++;
						}
						break;
					}
					*/
					Pawn *p = dynamic_cast<Pawn*>(board->getPreviousPlayedPiece());
					if (p != NULL && (p->getY() == 0 || p->getY() == board->BOARDSIZE-1)) {
						int x = p->getX();
						int y = p->getY();
						string promotion;

						cout << "Choose the new piece to promote the Pawn to." << endl;
						cin >> promotion;

						board->pawnPromotion((turn%2 == 0 ? 'B' : 'W'), x, y, promotion);

						// Redisplay with promoted piece
						textDisplay->print(cout);
					}

					turn++;
				}
			} else if (command == "setup") {
				if (playing) {
				 	cout << "Cannot enter setup mode while a game is in progress" << endl;
				} else if (board == NULL || player1 == NULL || player2 == NULL) {
					cout << "A game has not been started - enter game command to begin" << endl;
				} else {
 					setupMode();
 				}
			}
		}

		cout << "Play again? (y/n)" << endl;
	} while (cin >> playAgain);

	cout << "Final Score:" << endl;
	cout << "White: " << p2Score << endl;
	cout << "Black: " << p1Score << endl;

}

Controller::~Controller() {
	delete board;
	delete textDisplay;
	delete player1;
	delete player2;
	delete graphicDisplay;
}


