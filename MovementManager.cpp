#include <iostream>
#include "MovementManager.hpp"

MovementManager::MovementManager()
{}

bool MovementManager::isMoveValid(
	const wholeBoard& board, const std::vector<Piece>::iterator& pieceIter, std::pair<int, int> move)
{
	if (move.first < 0 || move.first > 7 || move.second < 0 || move.second > 7) // move out of scope
	{
		return false;
	}
	if (!board[move.second][move.first] == 'b') // white illegal field or 48 or 49
	{
		std::cout << "White illegal field or 48 or 49" << std::endl;
		return false;
	}
	if (!((*pieceIter).getPosition().first + 1 == move.first && (*pieceIter).getPosition().second - 1 == move.second) ||
		(*pieceIter).getPosition().first - 1 == move.first && (*pieceIter).getPosition().second - 1 == move.second) // check if the move is in the diagonal right/left direction
	{
		std::cout << "Check if the move is in the diagonal right/left direction" << std::endl;
		return false;
	}
	return true;
}