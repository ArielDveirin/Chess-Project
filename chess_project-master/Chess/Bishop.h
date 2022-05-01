#pragma once
#pragma message ("Bishop object defined")
#include "Piece.h"


class Bishop : public Piece {
public:
	Bishop(char type);
	virtual ~Bishop();
	virtual int move(Board* board, std::string move);
	virtual int checkMove(Board* board, std::string move);

};
