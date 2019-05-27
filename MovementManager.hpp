#pragma once

#include <utility>

#include "BoardManager.hpp"
#include "Piece.hpp"

class MovementManager
{
public:
	MovementManager(computerPieces& computerPieces);

	bool isMoveValid(
		wholeBoard& board, const std::vector<Piece>::iterator& pieceIter, std::pair<int, int> move, computerPieces& computerPieces);

private:
    void makeMove(wholeBoard& board, const std::vector<Piece>::iterator& pieceIter, std::pair<int, int> move);

    bool isCapturedPossible(wholeBoard& board, const std::vector<Piece>::iterator& pieceIter, std::pair<int, int> move);
    void tryToSpank(wholeBoard& board, const std::vector<Piece>::iterator& pieceIter, std::pair<int, int> move,
        int& numberOfSpanks, bool isRightDirection);
    void removeSpankedPiece(wholeBoard& board, bool isRightDirection, std::pair<int, int> move);

    computerPieces& computerPieces_;
};
