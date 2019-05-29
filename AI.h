#pragma once

#include "BoardManager.hpp"
#include "Piece.hpp"

class AI
{
public:
    AI(wholeBoard& board, computerPieces& computerPieces, playerPieces& playerPieces);

    int minmax(bool isComputer, wholeBoard board, computerPieces computerPieces, playerPieces playerPieces, int depth);

private:
    int calculateHeuristic(const wholeBoard& board);

    //Computer methods
    bool isAbilityToCaptured(wholeBoard& board, computerPieces& computerPieces, playerPieces& playerPieces, std::pair<int, int> computerPosition, int depth);
    void makeMove(wholeBoard& board, computerPieces& computerPieces, playerPieces& playerPieces,
        std::pair<int, int> computerPosition, std::pair<int, int> move, int depth);
    void removeSpankedPiece(wholeBoard& board, computerPieces& computerPieces, playerPieces& playerPieces,
        std::pair<int, int> move, bool isLeftDirection, int depth);

    wholeBoard& board_;
    computerPieces& computerPieces_;
    playerPieces& playerPieces_;
};
