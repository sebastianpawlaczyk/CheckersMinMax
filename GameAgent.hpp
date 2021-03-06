#pragma once

#include "BoardManager.hpp"
#include "Piece.hpp"

class GameAgent
{
public:
	GameAgent();
	void draw();
	void run();

private:
	BoardManager boardManager_;
	playerPieces playerPieces_;
	computerPieces computerPieces_;
};

