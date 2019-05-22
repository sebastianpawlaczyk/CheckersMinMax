#include "BoardManager.hpp"

#include <iostream>
#include <vector>

BoardManager::BoardManager()
{}

/**
 *	w - white field
 *	b - black field
  */
void BoardManager::createBoard()
{
	board_ =
		wholeBoard{std::vector<char>{'w', 'b', 'w', 'b', 'w', 'b', 'w', 'b'},
		std::vector<char>{'b', 'w', 'b', 'w', 'b', 'w', 'b', 'w'},
		std::vector<char>{'w', 'b', 'w', 'b', 'w', 'b', 'w', 'b'},
		std::vector<char>{'b', 'w', 'b', 'w', 'b', 'w', 'b', 'w'},
		std::vector<char>{'w', 'b', 'w', 'b', 'w', 'b', 'w', 'b'},
		std::vector<char>{'b', 'w', 'b', 'w', 'b', 'w', 'b', 'w'},
		std::vector<char>{'w', 'b', 'w', 'b', 'w', 'b', 'w', 'b'},
		std::vector<char>{'b', 'w', 'b', 'w', 'b', 'w', 'b', 'w'}};
}

wholeBoard& BoardManager::getBoard()
{
	return board_;
}

std::ostream& operator<<(std::ostream& os, const wholeBoard& board)
{
	for (const auto& i: board)
	{
		for (const auto& i2: i)
		{
			os << "\t" << i2;
		}
		os << std::endl;
	}
	return os;
}
