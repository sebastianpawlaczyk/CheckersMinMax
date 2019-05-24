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

    bool isCapturedPossible(const wholeBoard& board, const std::vector<Piece>::iterator& pieceIter, std::pair<int, int> move);
    void tryToSpank(const wholeBoard& board, const std::vector<Piece>::iterator& pieceIter, std::pair<int, int> move,
        int& numberOfSpanks, bool isRightDirection);
    void removeSpankedPiece(bool isRightDirection, std::pair<int, int> move);

    computerPieces& computerPieces_;
};
