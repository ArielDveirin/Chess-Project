#include "Knight.h"

Knight::Knight(char type) : Piece(type)
{
}

Knight::~Knight() {}

int Knight::move(Board* board, std::string move)
{
	int finalReturn = checkMove(board, move);
	Piece* temp = NULL;
	int moveIndices[4] = { move[0] - 'a', move[1] - '0' - 1,  move[2] - 'a', move[3] - '0' - 1 };


	if (!finalReturn)
	{
		//if there is a piece at the destination
		if (board->getPiece(moveIndices[3], moveIndices[2])) {
			//if both source and destination are the same 'color'(upper/lower)
			if (isupper(board->getPiece(moveIndices[3], moveIndices[2])->getType()) == isupper(this->_type))
			{
				finalReturn = 3;
			}
			//the destination is an enemy
			else
			{
				//delete the enemy(as it is going to be eaten)
				temp = board->getPiece(moveIndices[3], moveIndices[2]);
			}
		}

		//If all checks didnt change finalReturn from 0, then the move is valid. Make move.
		if (!finalReturn)
		{
			board->setPiece(moveIndices[3], moveIndices[2], this);
			board->setPiece(moveIndices[1], moveIndices[0], NULL);

			if (moveUtil::checkThreat(board, board->getKing(isupper(this->_type))))//if the color's king is in check after moving
			{
				finalReturn = 4;
				board->setPiece(moveIndices[1], moveIndices[0], this);//restoring the piece
				board->setPiece(moveIndices[3], moveIndices[2], temp);//restoring the enemy
			}
			else
			{
				if (temp) { delete temp; }//deleting the enemy, if there was one
				this->_hasMoved = true;
				//If after doing the move, opposite king is in check
				if (moveUtil::checkThreat(board, board->getKing(!isupper(this->_type))))
				{
					finalReturn = 1;
				}
			}
		}
	}
	return finalReturn;
}

int Knight::checkMove(Board* board, std::string move)
{
	int finalReturn = 0, letterDiff = 0, numberDiff = 0;
	int i = 0, j = 0;
	bool whileFlag = true;
	int moveIndices[4] = { move[0] - 'a', move[1] - '0' - 1,  move[2] - 'a', move[3] - '0' - 1 };

	////Bad Indices
	if (0 > moveIndices[2] || moveIndices[2] >= BOARD_SIZE || 0 > moveIndices[3] || moveIndices[3] >= BOARD_SIZE)
	{
		finalReturn = 5;
	}
	else if (move.substr(0, 2) == move.substr(2, 2))//same source and destination
	{
		finalReturn = 7;
	}
	else {//Checking move validity
		finalReturn = 6;//setting default as invalid
		
		letterDiff = abs(moveIndices[2] - moveIndices[0]);
		numberDiff = abs(moveIndices[3] - moveIndices[1]);
		if ((letterDiff == 2 && numberDiff == 1) || (letterDiff == 1 && numberDiff == 2))//valid move(2 in one line, 1 in the other)
		{
			finalReturn = 0;
		}
	}
	return finalReturn;
}