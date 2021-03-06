#pragma once

#include <utility>

#include "BoardManager.hpp"

/**
 * player =
 * 0 -> computer ASCII -> 48
 * 1 -> you ASCII -> 49
 * 2 -> not defined during initialization
 */
class Piece
{
public:
	Piece();
	void setPosition(int x, int y);
	void setKing();
	void setPlayer(int p);

	std::pair<int,int> getPosition() const;
	bool getIsKing() const;
	int getPlayer() const;

private:
	std::pair<int,int> position_;
	bool isKing_;
	int player_;
};

using playerPieces = std::vector<Piece>;
using computerPieces = std::vector<Piece>;
