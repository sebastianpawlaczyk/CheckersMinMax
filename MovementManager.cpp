#include <algorithm>
#include <iostream>

#include "MovementManager.hpp"

MovementManager::MovementManager(computerPieces& computerPieces)
: computerPieces_(computerPieces)
{}

bool MovementManager::isMoveValid(
	wholeBoard& board, const std::vector<Piece>::iterator& pieceIter, std::pair<int, int> move, computerPieces& computerPieces)
{
	if (move.first < 0 || move.first > 7 || move.second < 0 || move.second > 7) // move out of scope
	{
		std::cout << "Move out of scope" << std::endl;
		return false;
	}
	if (board[move.second][move.first] != 'b') // white illegal field or 48 or 49
	{
		std::cout << "White illegal field or 48 or 49" << std::endl;
		return false;
	}
	if (isCapturedPossible(board, pieceIter, move))
	{
		std::cout << "!!!!! " << move.first+2 << " ---  " << move.second-2 << std::endl;
		makeMove(board, pieceIter, move);
		isMoveValid(board, pieceIter,std::pair<int, int>{move.first+2, move.second-2}, computerPieces);
        isMoveValid(board, pieceIter,std::pair<int, int>{move.first-2, move.second-2}, computerPieces);
		return true;
	}
	if (!((*pieceIter).getPosition().first + 1 == move.first && (*pieceIter).getPosition().second - 1 == move.second ||
		(*pieceIter).getPosition().first - 1 == move.first && (*pieceIter).getPosition().second - 1 == move.second)) // check if the move is in the diagonal right/left direction
	{
		std::cout << "Check if the move is in the diagonal right/left direction" << std::endl;
		return false;
	}
	makeMove(board, pieceIter, move);
	return true;
}

bool MovementManager::isCapturedPossible(wholeBoard& board, const std::vector<Piece>::iterator& pieceIter, std::pair<int, int> move)
{
	bool isRightDirection = true;
	if ((*pieceIter).getPosition().first > move.first) // we try to spank by left diagonal
	{
		isRightDirection = false;
		std::cout << "if we do not have any piece to spank(left)" << std::endl;
		if (board[move.second + 1][move.first + 1] != '0') return false; // if we do not have any piece to spank
	}
	if ((*pieceIter).getPosition().first < move.first) // we try to spank by right diagonal
	{
		std::cout << "if we do not have any piece to spank(right)" << std::endl;
		if (board[move.second + 1][move.first - 1] != '0') return false; // if we do not have any piece to spank
	}
	int numberOfSpanks = 0;
	tryToSpank(board, pieceIter, move, numberOfSpanks, isRightDirection);
	return numberOfSpanks > 0;
}

void MovementManager::tryToSpank(wholeBoard &board, const std::vector<Piece>::iterator &pieceIter,
	std::pair<int, int> move, int& numberOfSpanks, bool isRightDirection)
{
	if (isRightDirection)
	{
		if ((*pieceIter).getPosition().first - 2 != move.first && (*pieceIter).getPosition().second - 2 != move.second)
		{
			return;
		}
	}
	if (!isRightDirection)
	{
		if (!(*pieceIter).getPosition().first + 2 != move.first && (*pieceIter).getPosition().second - 2 != move.second)
		{
			return;
		}
	}
	removeSpankedPiece(board, isRightDirection, move);
	numberOfSpanks++;
}

void MovementManager::removeSpankedPiece(wholeBoard& board, bool isRightDirection, std::pair<int, int> move)
{
	if (isRightDirection)
	{
		computerPieces_.erase(std::remove_if(computerPieces_.begin(), computerPieces_.end(), [&move](Piece &piece) {
			return (piece.getPosition().first == (move.first - 1) && piece.getPosition().second == (move.second + 1));
		}));
        board[move.second + 1][move.first - 1] = 'b';
	}
	if (!isRightDirection)
	{
		computerPieces_.erase(std::remove_if(computerPieces_.begin(), computerPieces_.end(), [&move](Piece &piece) {
			return (piece.getPosition().first == (move.first + 1) && piece.getPosition().second == (move.second + 1));
		}));
        board[move.second + 1][move.first + 1] = 'b';
	}
	for (const auto& i: computerPieces_)
	{
		std:: cout << i.getPosition().first << " y: " << i.getPosition().second << std::endl;
	}
}

void MovementManager::makeMove(wholeBoard& board, const std::vector<Piece>::iterator& pieceIter,
	std::pair<int, int> move)
{
	board[move.second][move.first] = '1';
	board[(*pieceIter).getPosition().second][(*pieceIter).getPosition().first] = 'b';
	(*pieceIter).setPosition(move.first,  move.second);
}