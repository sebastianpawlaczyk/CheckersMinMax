#include "GameAgent.hpp"

#include <iostream>

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
			if (fieldCounter < 24 && j == 'b') j = 48;
			if (fieldCounter > 39 && j == 'b') j = 49;
			fieldCounter++;
		}
	}
	std::cout << this->boardManager_.getBoard();
}