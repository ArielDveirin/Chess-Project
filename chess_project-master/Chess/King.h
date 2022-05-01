#pragma once
#pragma message ("King object defined")
#include "Piece.h"

class King : public Piece{
public:
	King(char type);
	virtual ~King();
	virtual int move(Board* board, std::string move);
	virtual int checkMove(Board* board, std::string move);

};

