#pragma once
#pragma message ("Queen object defined")
#include "Piece.h"

class Queen : public Piece {
public:
	Queen(char);
	virtual ~Queen();
	virtual int move(Board* board, std::string move);
	virtual int checkMove(Board* board, std::string move);

};

