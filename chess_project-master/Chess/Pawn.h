#pragma once
#pragma message ("Pawn object defined")
#include "Piece.h"

class Pawn : public Piece {
public:
	Pawn(char);
	virtual ~Pawn();
	virtual int move(Board* board, std::string move);
	virtual int checkMove(Board* board, std::string move);

};

