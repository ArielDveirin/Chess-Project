#pragma once
#include "Board.h"

class moveUtil {
private:
	static bool checkMovement(Board* board, std::vector<int> place, const int iInc, const int jInc, const bool type);

public:
	static int diagonalMove(Board* board, int moveIndices[]);
	static int horiVertMove(Board* board, int moveIndices[]);

	static bool checkThreat(Board* board, std::vector<int> placeInd);


};