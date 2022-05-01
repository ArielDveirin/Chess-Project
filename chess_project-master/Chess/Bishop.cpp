#include "Bishop.h"

Bishop::Bishop(char type) : Piece(type) {}

Bishop:: ~Bishop() {};

int Bishop:: move(Board* board, std::string move)
{
	
	int finalReturn = checkMove(board, move);
	Piece* temp = NULL;
	int moveIndices[4] = { move[0] - 'a', move[1] - '0' - 1,  move[2] - 'a', move[3] - '0' - 1 };


	if (!finalReturn)
	{

		//if there is a piece at the destination
		if (board->getPiece(moveIndices[3], moveIndices[2])) {
			//if both source and destination are the same 'color'(upper/lower)
			if (isupper(board->getPiece(moveIndices[3], moveIndices[2])->getType()) == isupper(board->getPiece(moveIndices[1], moveIndices[0])->getType()))
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
			board->setPiece(moveIndices[3], moveIndices[2], board->getPiece(moveIndices[1], moveIndices[0]));
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

int Bishop:: checkMove(Board* board, std::string move)
{
	int finalReturn = 0;
	int moveIndices[4] = { move[0] - 'a', move[1] - '0' - 1,  move[2] - 'a', move[3] - '0' - 1 };

	////Bad Indices
	if (0 > moveIndices[2] || moveIndices[2] >= BOARD_SIZE || 0 > moveIndices[3] || moveIndices[3] >= BOARD_SIZE)
	{
		finalReturn = 5;
	}
	else if (moveIndices[0] == moveIndices[2] || moveIndices[1] == moveIndices[3])//Illegal bishop move(a2b2 for example)
	{
		finalReturn = 6;
	}
	else if (abs(moveIndices[2] - moveIndices[0]) != abs(moveIndices[3] - moveIndices[1]))
	{
		finalReturn = 6;
	}
	else if (move.substr(0, 2) == move.substr(2, 2))//same source and destination
	{
		finalReturn = 7;
	}
	else 
	{
		finalReturn = moveUtil::diagonalMove(board, moveIndices);
	}
	return finalReturn;

}