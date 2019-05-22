#include "Piece.hpp"

#include <assert.h>

Piece::Piece()
: position_(0,0),
  	isKing_(false),
  	player_(2)
{}

void Piece::setPosition(int x, int y)
{
	position_.first = x;
	position_.second = y;
}

void Piece::setKing()
{
	isKing_ = true;
}

void Piece::setPlayer(int p)
{
	assert(p == 0 || p == 1);
	player_ = p;
}

std::pair<int,int> Piece::getPosition() const
{
	return position_;
}

bool Piece::getIsKing() const
{
	return isKing_;
}

int Piece::getPlayer() const
{
	return player_;
}