#include <iostream>
#include "AI.h"

static int max = -12;
static int min = 12;

AI::AI(wholeBoard& board, computerPieces& computerPieces, playerPieces& playerPieces)
: board_(board),
    computerPieces_(computerPieces),
    playerPieces_(playerPieces)
{}

int AI::minmax(bool isComputer, wholeBoard board, int depth)
{
    depth++;
    if (depth == 3)
    {
        std::cout << calculateHeuristic(board) << " !!!";
        return calculateHeuristic(board);
    }
    wholeBoard fakeBoard = board;
    if (isComputer)
    {
        for (auto &i : computerPieces_)
        {
            std::pair<int, int> possibleMove;
            bool inScope;

            possibleMove.first = i.getPosition().first - 1;
            possibleMove.second = i.getPosition().second + 1;
            inScope = true;

            if (possibleMove.first < 0 || possibleMove.second < 0)
            {
                inScope = false;
            }
            if (inScope && fakeBoard[possibleMove.second][possibleMove.first] == 'b') // left diagonal move
            {
                std::cout << "Depth " << depth << " CP_Piece x:" << i.getPosition().first
                          << " y: " << i.getPosition().second
                          << " MOVE x: " << possibleMove.first << " y: " << possibleMove.second << std::endl;
                fakeBoard[i.getPosition().second][i.getPosition().first] = 'b';
                fakeBoard[possibleMove.second][possibleMove.first] = '0';
                int pom = minmax(false, fakeBoard, depth);
                if (pom > max) max = pom;
                fakeBoard = board;
            }

            possibleMove.first = i.getPosition().first + 1;
            possibleMove.second = i.getPosition().second + 1;
            inScope = true;

            if (possibleMove.first > 7 || possibleMove.second > 7)
            {
                inScope = false;
            }
            if (inScope && fakeBoard[possibleMove.second][possibleMove.first] == 'b') // right diagonal move
            {
                std::cout << "Depth " << depth << " CP_Piece x:" << i.getPosition().first
                          << " y: " << i.getPosition().second
                          << " MOVE x: " << possibleMove.first << " y: " << possibleMove.second << std::endl;
                fakeBoard[i.getPosition().second][i.getPosition().first] = 'b';
                fakeBoard[possibleMove.second][possibleMove.first] = '0';
                int pom = minmax(false, fakeBoard, depth);
                if (pom > max) max = pom;
                fakeBoard = board;
            }
        }
    }

    else
    {
        for (auto& i : playerPieces_)
        {
            std::pair<int, int> possibleMove;
            bool inScope;

            possibleMove.first = i.getPosition().first - 1;
            possibleMove.second = i.getPosition().second - 1;
            inScope = true;

            if (possibleMove.first < 0 || possibleMove.second < 0)
            {
                inScope = false;
            }
            if (inScope && fakeBoard[possibleMove.second][possibleMove.first] == 'b') // left diagonal move
            {
                std::cout << "Depth " << depth << " P_Piece x:" << i.getPosition().first
                          << " y: " << i.getPosition().second
                          << " MOVE x: " << possibleMove.first << " y: " << possibleMove.second << std::endl;
                fakeBoard[i.getPosition().second][i.getPosition().first] = 'b';
                fakeBoard[possibleMove.second][possibleMove.first] = '1';
                int pom = minmax(true, fakeBoard, depth);
                if (pom < min) min = pom;
                fakeBoard = board;
            }

            possibleMove.first = i.getPosition().first + 1;
            possibleMove.second = i.getPosition().second - 1;
            inScope = true;

            if (possibleMove.first > 7 || possibleMove.second > 7)
            {
                inScope = false;
            }
            if (inScope && fakeBoard[possibleMove.second][possibleMove.first] == 'b') // right diagonal move
            {
                std::cout << "Depth " << depth << " P_Piece x:" << i.getPosition().first
                          << " y: " << i.getPosition().second
                          << " MOVE x: " << possibleMove.first << " y: " << possibleMove.second << std::endl;
                fakeBoard[i.getPosition().second][i.getPosition().first] = 'b';
                fakeBoard[possibleMove.second][possibleMove.first] = '1';
                int pom = minmax(true, fakeBoard, depth);
                if (pom < min) min = pom;
                fakeBoard = board;
            }
        }
    }
}

int AI::calculateHeuristic(wholeBoard board)
{
    int computerPieces = 0;
    int playerPieces = 0;
    for (const auto& i : board)
    {
        for (const auto& j: i)
        {
            if (j == '0') computerPieces++;
            if (j == '1') playerPieces++;
        }
    }
    return computerPieces - playerPieces;
}