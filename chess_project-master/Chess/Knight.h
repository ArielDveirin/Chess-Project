#pragma once
#pragma message ("Knight object defined")
#include "Piece.h"

class Knight : public Piece {
public:
	Knight(char);
	virtual ~Knight();
	virtual int move(Board* board, std::string move);
	virtual int checkMove(Board* board, std::string move);

};

