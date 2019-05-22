#pragma once

#include <utility>

#include "BoardManager.hpp"
#include "Piece.hpp"

class MovementManager
{
public:
	MovementManager();

	bool isMoveValid(
		const wholeBoard& board, const std::vector<Piece>::iterator& pieceIter, std::pair<int, int> move);
};
