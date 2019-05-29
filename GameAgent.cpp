#include "GameAgent.hpp"

#include <algorithm>
#include <iostream>
#include <syslog.h>
#include "AI.h"
#include "MovementManager.hpp"

GameAgent::GameAgent()
{
}

void GameAgent::draw()
{
	this->boardManager_.createBoard();

	int fieldCounter = 0;
	//I will get i = std::vector<char>
	for (auto& i : this->boardManager_.getBoard())
	{
		//I will get j = char
		for (auto& j : i)
		{
			if (fieldCounter >= 24 && fieldCounter <= 39)
			{
				fieldCounter++;
				continue;
			}
			if (fieldCounter < 24 && j == 'b')
			{
				auto piece = Piece();
				piece.setPlayer(0);
				piece.setPosition(fieldCounter % 8, fieldCounter / 8); // row -> fieldCounter % 8 || column -> fieldCounter / 8
				this->computerPieces_.push_back(piece);
				j = 48;
			}
			if (fieldCounter > 39 && j == 'b')
			{
				auto piece = Piece();
				piece.setPlayer(0);
				piece.setPosition(fieldCounter % 8, fieldCounter / 8); // row -> fieldCounter % 8 || column -> fieldCounter / 8
				this->playerPieces_.push_back(piece);
				j = 49;
			}
			fieldCounter++;
		}
	}
	std::cout << this->boardManager_.getBoard() << std::endl;
}

void GameAgent::run()
{
    MovementManager move(computerPieces_);
	int x, y;

	while (true)
	{
	    //-----------------playerMove----------------------------------------------------------------
		std::cout << "Choose piece" << std::endl;
		std::cout << "(x,y) after whitespace, e.x -> 4 7" << std::endl;

		std::vector<Piece>::iterator pieceIter;
		while (true)
		{
			std::cout << "Waiting..." << std::endl;
			std::cin >> x >> y;
			pieceIter = std::find_if(this->playerPieces_.begin(), this->playerPieces_.end(),
				[x, y](Piece &piece) { return piece.getPosition().first == x && piece.getPosition().second == y; });

			if (pieceIter != this->playerPieces_.end()) {
				break;
			}
			std::cout << "Wrong co-ordinates -> try again" << std::endl;
		}

		std::cout << "Choose move" << std::endl;
		std::cout << "(x,y) after whitespace, e.x -> 4 7" << std::endl;
		bool isMoveValid = false;

		while (!isMoveValid)
		{
			std::cout << "Waiting..." << std::endl;
			std::cin >> x >> y;
			isMoveValid = move.isMoveValid(boardManager_.getBoard(), pieceIter, std::pair<int, int>{x, y}, computerPieces_);
		}

		isMoveValid = false;

        AI ai(boardManager_.getBoard(), computerPieces_, playerPieces_);
        ai.minmax(true, boardManager_.getBoard(), computerPieces_, playerPieces_, 0);

        //GUI
		std::cout << std::endl << "----------------------------------------" << std::endl;
        std::cout << this->boardManager_.getBoard() << std::endl;
        std::cout << "Computer Pieces: " << this->computerPieces_.size() << std::endl;
        for (const auto& i : computerPieces_)
        {
            std::cout << "x : " << i.getPosition().first << " y: " << i.getPosition().second << std::endl;
        }
        std::cout << "Player Pieces: " << this->playerPieces_.size() << std::endl;
        for (const auto& i : playerPieces_)
        {
            std::cout << "x : " << i.getPosition().first << " y: " << i.getPosition().second << std::endl;
        }
	}
}
