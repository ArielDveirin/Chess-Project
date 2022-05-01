#include "Pawn.h"

Pawn::Pawn(char type) : Piece(type)
{
}

Pawn::~Pawn() {}

int Pawn::move(Board* board, std::string move)
{
	int finalReturn = checkMove(board, move);

	int moveIndices[4] = { move[0] - 'a', move[1] - '0' - 1,  move[2] - 'a', move[3] - '0' - 1 };
	Piece* temp = NULL;

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
			//testing move
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

int Pawn::checkMove(Board* board, std::string move)
{
	int finalReturn = 0;
	int cellsAllowed = 1;//number of cell movement allowed(2 for starting location as white)
	int extraCell = 0;
	int moveIndices[4] = { move[0] - 'a', move[1] - '0' - 1,  move[2] - 'a', move[3] - '0' - 1 };

	//Bad Indexes
	if (0 > moveIndices[2] || moveIndices[2] >= BOARD_SIZE || 0 > moveIndices[3] || moveIndices[3] >= BOARD_SIZE)
	{
		finalReturn = 5;
	}
	else if (move.substr(0, 2) == move.substr(2, 2))//same source and destination
	{
		finalReturn = 7;
	}
	else
	{
		//Checking if its a legal move

		//Checking how many cells it can move(1/2)
			//if White
		if (isupper(board->getPiece(moveIndices[1], moveIndices[0])->getType()))
		{
			cellsAllowed = 1;
			if (moveIndices[1] == 1)//is in starting 'line'
			{
				extraCell = 1;
			}
		}
		else//if Black
		{
			cellsAllowed = -1;
			if (moveIndices[1] == 6)//is in starting 'line'
			{
				extraCell = -1;
			}
		}

		//checking the change in the letter index
		if (abs(moveIndices[0] - moveIndices[2]) > 1)//if the move is more than one letter
		{
			finalReturn = 6;//illegal move
		}
		else if (abs(moveIndices[0] - moveIndices[2]) == 1)//if the letters are different in exactly one letter(From source and dest)
		{
			if (board->getPiece(moveIndices[3], moveIndices[2]))//if there is a piece in the destination
			{
				//if the change in numbers is not only 1(a take is 1 diagonally exactly)
				if (moveIndices[3] - moveIndices[1] != 2 * (bool)isupper(this->_type) - 1)
				{
					finalReturn = 6;
				}
			}
			else
			{
				finalReturn = 6;//pawn is trying to move diagonally without eating
			}
		}
		else//the move is just a standard move(in the same letter)
		{
			if (!board->getPiece(moveIndices[3], moveIndices[2]))//if there is a piece, we cant move there.
			{
				cellsAllowed += extraCell;//2 1110
				if (cellsAllowed > 0)//if we are white
				{
					if (moveIndices[3] - moveIndices[1] > cellsAllowed || moveIndices[3] - moveIndices[1] < 0)
					{
						finalReturn = 6;//illegal move, the pawn is trying to move more than the number of allowed cells
					}
					else if (moveIndices[3] - moveIndices[1] == 2 && board->getPiece(moveIndices[3] -1, moveIndices[2]))
					{
						finalReturn = 6;
					}
				}
				else
				{
					if (moveIndices[3] - moveIndices[1] < cellsAllowed || moveIndices[3] - moveIndices[1] > 0)
					{
						finalReturn = 6;
					}
					else if (moveIndices[3] - moveIndices[1] == -2 && board->getPiece(moveIndices[3] + 1, moveIndices[2]))
					{
						finalReturn = 6;
					}
				}
			}
			else
			{
				finalReturn = 6;//there is a piece at the destination
			}
		}
	}
	

	return finalReturn;
}