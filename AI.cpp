#include <iostream>
#include <algorithm>
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
            std::pair<int, int> computerPosition;
            bool inScope;

            possibleMove.first = i.getPosition().first - 1;
            possibleMove.second = i.getPosition().second + 1;
            inScope = true;

            computerPosition.first = i.getPosition().first;
            computerPosition.second = i.getPosition().second;
            if(isAbilityToCaptured(fakeBoard, computerPosition)) // check if computer can spank
            {
                if (depth == 1) // if it's on the firs level of tree we skip next recursions and move
                {
                    std::cout << "COMPUTER MAKE AN ATTACK!!!" << std::endl;
                    return 13;
                }
            }

            if (possibleMove.first < 0 || possibleMove.second > 7)
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

int AI::calculateHeuristic(const wholeBoard& board)
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

bool AI::isAbilityToCaptured(wholeBoard& board, std::pair<int, int> computerPosition)
{
    std::pair<int, int> possibleMove;
    bool inScope;
    bool isLeftDirection;

    possibleMove.first = computerPosition.first - 2;
    possibleMove.second = computerPosition.second + 2;
    inScope = true;

    if (possibleMove.first < 0 || possibleMove.second > 7)
    {
        inScope = false;
    }
    if (inScope && board[possibleMove.second][possibleMove.first] == 'b')
    {
        if (board[possibleMove.second -1][possibleMove.first + 1] == '1') // left direction
        {
            isLeftDirection = true;
            makeMove(board_, computerPosition, possibleMove);
            removeSpankedPiece(board_, possibleMove, isLeftDirection);
            isAbilityToCaptured(board_, std::pair<int, int>{possibleMove.first, possibleMove.second});
            return true;
        }
    }
    return false;
}

void AI::makeMove(wholeBoard& board, std::pair<int, int> computerPosition, std::pair<int, int> move)
{
    board[move.second][move.first] = '0';
    board[computerPosition.second][computerPosition.first] = 'b';

    //change computer position
    auto cp_piece = std::find_if(computerPieces_.begin(), computerPieces_.end(), [&move,&computerPosition](Piece& piece) {
        return (piece.getPosition().first == (computerPosition.first) && piece.getPosition().second == (computerPosition.second));
    });
    (*cp_piece).setPosition(move.first, move.second);
}

void AI::removeSpankedPiece(wholeBoard& board, std::pair<int, int> move, bool isLeftDirection)
{
    // remove player spanked piece
    if (isLeftDirection)
    {
        playerPieces_.erase(std::find_if(playerPieces_.begin(), playerPieces_.end(), [&move](Piece &piece) {
            return (piece.getPosition().first == (move.first + 1) && piece.getPosition().second == (move.second - 1));
        }));
        board[move.second - 1][move.first + 1] = 'b';
    }
    if (!isLeftDirection)
    {

    }
}