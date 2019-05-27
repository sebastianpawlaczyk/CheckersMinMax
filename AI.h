#pragma once

#include "BoardManager.hpp"
#include "Piece.hpp"

class AI
{
public:
    AI(wholeBoard& board, computerPieces& computerPieces, playerPieces& playerPieces);

    int minmax(bool isComputer, wholeBoard board, int depth);

private:
    int calculateHeuristic(const wholeBoard& board);

    //Computer methods
    bool isAbilityToCaptured(wholeBoard& board, std::pair<int, int> computerPosition);
    void makeMove(wholeBoard& board, std::pair<int, int> computerPosition,
        std::pair<int, int> move);
    void removeSpankedPiece(wholeBoard& board, std::pair<int, int> move, bool isLeftDirection);

    wholeBoard& board_;
    computerPieces& computerPieces_;
    playerPieces& playerPieces_;
};
