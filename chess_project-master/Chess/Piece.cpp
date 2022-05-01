#include "Piece.h"

Piece::Piece(char type)
{
	_type = type;
	_hasMoved = false;
}

Piece::~Piece() {};

char Piece::getType()
{
	return this->_type;
}

bool Piece::getHasMoved()
{
	return this->_hasMoved;
}