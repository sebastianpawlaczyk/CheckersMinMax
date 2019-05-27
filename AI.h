#pragma once

#include "BoardManager.hpp"
#include "Piece.hpp"

class AI
{
public:
    AI(wholeBoard& board, computerPieces& computerPieces, playerPieces& playerPieces);

    int minmax(bool isComputer, wholeBoard board, int depth);

private:
    int calculateHeuristic(wholeBoard board);

    wholeBoard& board_;
    computerPieces& computerPieces_;
    playerPieces& playerPieces_;
};
