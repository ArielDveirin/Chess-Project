#pragma once
#pragma message ("Piece object defined")
#include "Board.h"

class Board;
class moveUtil;
#include "moveUtil.h"

class Piece 
{
protected:
	char _type;
	bool _hasMoved;
public:
	Piece(char type);
	virtual ~Piece();
	virtual int move(Board* board, std::string move) = 0;
	virtual int checkMove(Board* board, std::string move) = 0;

	char getType();
	bool getHasMoved();
};
#pragma message ("Piece class def")
