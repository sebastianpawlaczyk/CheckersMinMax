#pragma once

#include <ostream>
#include <vector>

using wholeBoard = std::vector<std::vector<char>>;

class BoardManager
{
public:
	BoardManager();
	void createBoard();
	wholeBoard& getBoard();

private:
	wholeBoard board_;

};

std::ostream& operator<<(std::ostream& os, const wholeBoard& board);
