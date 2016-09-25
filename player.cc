#include "player.h"

using namespace std;

Player::Player(Board *board, char team) {
	this->board = board;
	this->team = team;
}

Player::~Player() {}


