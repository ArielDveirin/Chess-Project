#pragma once
#pragma message ("Rook object defined")
#include "Piece.h"

class Rook : public Piece{
public:
	Rook(char);
	virtual ~Rook();
	virtual int move(Board* board, std::string move);
	virtual int checkMove(Board* board, std::string move);
	
};

