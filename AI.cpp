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

int AI::minmax(bool isComputer, wholeBoard board, computerPieces CP_Pieces, playerPieces P_Pieces, int depth)
{
    depth++;
    if (depth == 3)
    {
        std::cout << calculateHeuristic(board) << " !!!";
        return calculateHeuristic(board);
    }
    wholeBoard fakeBoard = board;
    computerPieces computerFakePieces = CP_Pieces;
    playerPieces playerFakePieces = P_Pieces;
    if (isComputer)
    {
        for (auto &i : computerFakePieces)
        {
            std::pair<int, int> possibleMove;
            std::pair<int, int> computerPosition;
            bool inScope;

            possibleMove.first = i.getPosition().first - 1;
            possibleMove.second = i.getPosition().second + 1;
            inScope = true;

            computerPosition.first = i.getPosition().first;
            computerPosition.second = i.getPosition().second;
            if(isAbilityToCaptured(fakeBoard, computerFakePieces, playerFakePieces, computerPosition, depth)) // check if computer can spank
            {
                if (depth == 1) // if it's on the firs level of tree we skip next recursions and move
                {
                    std::cout << "COMPUTER MAKE AN ATTACK!!!" << std::endl;
                    return 13;
                }
                std::cout << "Depth " << depth << " CP_Piece x:" << computerPosition.first
                          << " y: " << computerPosition.second
                          << " ATTACK_MOVE x: " << i.getPosition().first << " y: " << i.getPosition().second << std::endl;
                int pom = minmax(false, fakeBoard, computerFakePieces, playerFakePieces, depth);
                fakeBoard = board;
                continue;
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
                int pom = minmax(false, fakeBoard, computerFakePieces, playerFakePieces, depth);
                if (pom > max) max = pom;
                fakeBoard = board;
            }

            possibleMove.first = possibleMove.first + 2;
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
                int pom = minmax(false, fakeBoard, computerFakePieces, playerFakePieces, depth);
                if (pom > max) max = pom;
                fakeBoard = board;
            }
        }
    }

    else
    {
        for (auto& i : playerFakePieces)
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
                int pom = minmax(true, fakeBoard, computerFakePieces, playerFakePieces, depth);
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
                int pom = minmax(true, fakeBoard, computerFakePieces, playerFakePieces, depth);
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

bool AI::isAbilityToCaptured(wholeBoard& board, computerPieces& computerPieces, playerPieces& playerPieces, std::pair<int, int> computerPosition, int depth)
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
        if (board[possibleMove.second - 1][possibleMove.first + 1] == '1') // left direction
        {
            isLeftDirection = true;
            if (depth == 1)
            {
                makeMove(board_, computerPieces_, playerPieces_, computerPosition, possibleMove, depth);
                removeSpankedPiece(board_, computerPieces_ , playerPieces_, possibleMove, isLeftDirection,depth);
                isAbilityToCaptured(board_, computerPieces_, playerPieces_, std::pair<int, int>{possibleMove.first, possibleMove.second}, depth);
                return true;
            }
            makeMove(board, computerPieces, playerPieces, computerPosition, possibleMove, depth);
            removeSpankedPiece(board, computerPieces, playerPieces, possibleMove, isLeftDirection, depth);
            isAbilityToCaptured(board, computerPieces, playerPieces, std::pair<int, int>{possibleMove.first, possibleMove.second}, depth);
            return true;
        }
    }

    possibleMove.first = computerPosition.first + 2;
    possibleMove.second = computerPosition.second + 2;
    inScope = true;

    if (possibleMove.first < 0 || possibleMove.second > 7)
    {
        inScope = false;
    }
    if (inScope && board[possibleMove.second][possibleMove.first] == 'b')
    {
        if (board[possibleMove.second - 1][possibleMove.first - 1] == '1') // right direction
        {
            isLeftDirection = false;
            if (depth == 1)
            {
                makeMove(board_, computerPieces_, playerPieces_, computerPosition, possibleMove, depth);
                removeSpankedPiece(board_, computerPieces_ , playerPieces_, possibleMove, isLeftDirection,depth);
                isAbilityToCaptured(board_, computerPieces_, playerPieces_, std::pair<int, int>{possibleMove.first, possibleMove.second}, depth);
                return true;
            }
            makeMove(board, computerPieces, playerPieces, computerPosition, possibleMove, depth);
            removeSpankedPiece(board, computerPieces, playerPieces, possibleMove, isLeftDirection, depth);
            isAbilityToCaptured(board, computerPieces, playerPieces, std::pair<int, int>{possibleMove.first, possibleMove.second}, depth);
            return true;
        }
    }
    return false;
}

void AI::makeMove(wholeBoard& board, computerPieces& computerPieces, playerPieces& playerPieces, std::pair<int, int> computerPosition, std::pair<int, int> move, int depth) {

    board[move.second][move.first] = '0';
    board[computerPosition.second][computerPosition.first] = 'b';
    if (depth == 1)
    {
        //change computer position
        auto cp_piece = std::find_if(computerPieces_.begin(), computerPieces_.end(),
        [&move, &computerPosition](Piece &piece) {
            return (piece.getPosition().first == (computerPosition.first) &&
                    piece.getPosition().second == (computerPosition.second));
        });
    (*cp_piece).setPosition(move.first, move.second);
    }
    else
    {
        //change computer position
        auto cp_piece = std::find_if(computerPieces.begin(), computerPieces.end(), [&move,&computerPosition](Piece& piece) {
            return (piece.getPosition().first == (computerPosition.first) && piece.getPosition().second == (computerPosition.second));
        });
        (*cp_piece).setPosition(move.first, move.second);
    }
}

void AI::removeSpankedPiece(wholeBoard& board, computerPieces& computerPieces, playerPieces& playerPieces, std::pair<int, int> move, bool isLeftDirection, int depth)
{
    if (depth == 1)
    {
        // remove player spanked piece
        if (isLeftDirection) {
            playerPieces_.erase(std::find_if(playerPieces_.begin(), playerPieces_.end(), [&move](Piece &piece) {
                return (piece.getPosition().first == (move.first + 1) &&
                        piece.getPosition().second == (move.second - 1));
            }));
            board[move.second - 1][move.first + 1] = 'b';
        }
        if (!isLeftDirection) {
            playerPieces_.erase(std::find_if(playerPieces_.begin(), playerPieces_.end(), [&move](Piece &piece) {
                return (piece.getPosition().first == (move.first - 1) &&
                        piece.getPosition().second == (move.second - 1));
            }));
            board[move.second - 1][move.first - 1] = 'b';
        }
    }
    else
    {
        // remove player spanked piece
        if (isLeftDirection) {
            playerPieces.erase(std::find_if(playerPieces.begin(), playerPieces.end(), [&move](Piece &piece) {
                return (piece.getPosition().first == (move.first + 1) &&
                        piece.getPosition().second == (move.second - 1));
            }));
            board[move.second - 1][move.first + 1] = 'b';
        }
        if (!isLeftDirection) {
            playerPieces.erase(std::find_if(playerPieces.begin(), playerPieces.end(), [&move](Piece &piece) {
                return (piece.getPosition().first == (move.first - 1) &&
                        piece.getPosition().second == (move.second - 1));
            }));
            board[move.second - 1][move.first - 1] = 'b';
        }
    }
}