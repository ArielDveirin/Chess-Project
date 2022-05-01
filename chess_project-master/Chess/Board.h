#pragma once
#pragma message ("Board object defined")
#include <iostream>
#include <string>
#include <cctype>
#include <vector>

class Piece;

#include "Piece.h"



#define BOARD_SIZE 8
#define MOVE_STR_SIZE 4
class Board {
private:
	bool _turn;
	std::vector<int> _kings;
	std::vector<std::vector<Piece*>> _board;

public:
	Board(std::string base);
	
	void print() const;
	
	bool getTurn() const;
	void setTurn(const bool turn);

	std::vector<std::vector<Piece*>> getBoard() const;
	void setPiece(int number, int letter, Piece* piece);
	Piece* getPiece(int number, int letter);

	void updateKings(int type, int letter, int number);
	std::vector<int> getKing(int type);

};

