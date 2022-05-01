#include "moveUtil.h"

/*
Function that gets the board and the move to check,
and checks if its a valid diagonal move(for a bishop for example)
returns 0 if valid, 6 if invalid
*/
int moveUtil::diagonalMove(Board* board, int moveIndices[])
{
	int letterInc = 0, numberInc = 0, finalReturn = 0;
	int i = 0, j = 0;
	bool whileFlag = true;
	//if the bishop tries to move more than 1 cell
	//we want to check if theres is is anything between the source and destination
	if (abs(moveIndices[1] - moveIndices[3]) == abs(moveIndices[0] - moveIndices[2]))//if its not a bishop move
	{
		if (abs(moveIndices[1] - moveIndices[3]) + abs(moveIndices[0] - moveIndices[2]) != 2)
		{

			if (moveIndices[2] > moveIndices[0])
			{
				letterInc = 1;
			}
			else
			{
				letterInc = -1;
			}

			if (moveIndices[3] > moveIndices[1])
			{
				numberInc = 1;
			}
			else
			{
				numberInc = -1;
			}

			i = moveIndices[1] + numberInc;
			j = moveIndices[0] + letterInc;

			while (whileFlag && finalReturn == 0)
			{

				if (j == moveIndices[2] - letterInc && i == moveIndices[3] - numberInc)
				{
					whileFlag = false;
				}

				if (board->getPiece(i, j))//if a piece exists
				{
					finalReturn = 6;
				}

				i += numberInc;
				j += letterInc;
			}
		}
	}
	else
	{
		finalReturn = 6;
	}

	return finalReturn;
}

/*
Function that gets the board and the move to check,
and checks if its a valid horizontal/vertical move(for a rook for example)
returns 0 if valid, 6 if invalid
*/
int moveUtil::horiVertMove(Board* board, int moveIndices[])
{
	int finalReturn = 0, letterInc = 0, numberInc = 0;
	int i = 0, j = 0;
	bool whileFlag = true;

	//if the rook tries to move more than 1 cell
	//we want to check if theres is is anything between the source and destination
	if (moveIndices[0] == moveIndices[2] || moveIndices[1] == moveIndices[3])
	{

		if (abs(moveIndices[1] - moveIndices[3]) + abs(moveIndices[0] - moveIndices[2]) != 1)
		{
			//the rook moves up or down.
			if (moveIndices[0] == moveIndices[2])
			{
				if (moveIndices[1] > moveIndices[3])
				{
					numberInc = -1;
				}
				else
				{
					numberInc = 1;
				}
			}
			else//the Rook moves right or left.
			{
				if (moveIndices[0] > moveIndices[2])
				{
					letterInc = -1;
				}

				else
				{
					letterInc = 1;
				}

			}

			i = moveIndices[1] + numberInc;
			j = moveIndices[0] + letterInc;

			while (whileFlag && finalReturn == 0)
			{
				if ((letterInc && j == moveIndices[2] - letterInc) || (numberInc && i == moveIndices[3] - numberInc))
				{
					whileFlag = false;
				}

				if (board->getPiece(i, j))//if a piece exists
				{
					finalReturn = 6;
				}

				i += numberInc;
				j += letterInc;
			}
		}
	}
	else
	{
		finalReturn = 6;
	}
	return finalReturn;
}



bool moveUtil::checkMovement(Board* board, const std::vector<int> place, const int iInc, const int jInc, const bool type)
{
	int i = place[1], j = place[0];
	bool checked = false;
	bool whileFlag = true;
	char currType = ' ';
	i += iInc;
	j += jInc;

	while (whileFlag)
	{
		if (i < 0 || i > BOARD_SIZE || j < 0 || j > BOARD_SIZE)//off indexes
		{
			whileFlag = false;
		}
		else
		{
			if (board->getPiece(i, j))//if there is a piece
			{
				currType = board->getPiece(i, j)->getType();
				checked = (currType == ('q' - 32 * (bool)!type));//checking if there is a rook or a queen of the opposite color

				if (iInc == 0 || jInc == 0)//if its a rook move
				{
					checked = checked || (currType == ('r' - 32 * (bool)!type));
				}
				else//its a bishop move
				{
					checked = checked || (currType == ('b' - 32 * (bool)!type));
				}
				//we stop the while(because we encountered a piece
				whileFlag = false;
			}
			i += iInc;
			j += jInc;
		}
	}
	return checked;
}

/*
Function that checks if the king is in check.
*/
bool moveUtil::checkThreat(Board* board, std::vector<int> placeInd)
{
	bool checked = false;
	int pawnCheck = 0;
	bool type = isupper(board->getPiece(placeInd[1], placeInd[0])->getType());//king white/black
	//Queen || Rook Checks
	if (placeInd[1] != 0)
	{
		checked = checkMovement(board, placeInd, -1, 0, type);
	}
	if (!checked && placeInd[1] != 7)
	{
		checked = checkMovement(board, placeInd, 1, 0, type);
	}
	if (!checked && placeInd[0] != 0)
	{
		checked = checkMovement(board, placeInd, 0, -1, type);
	}
	if (!checked && placeInd[0] != 7)
	{
		checked = checkMovement(board, placeInd, 0, 1, type);
	}

	//Queen || Bishop Checks
	if (!checked && placeInd[1] != 0 && placeInd[0] != 7)
	{
		checked = checkMovement(board, placeInd, -1, 1, type);
	}
	if (!checked && placeInd[1] != 0 && placeInd[0] != 0)
	{
		checked = checkMovement(board, placeInd, -1, -1, type);
	}
	if (!checked && placeInd[1] != 7 && placeInd[0] != 0)
	{
		checked = checkMovement(board, placeInd, 1, -1, type);
	}
	if (!checked && placeInd[1] != 7 && placeInd[0] != 7)
	{
		checked = checkMovement(board, placeInd, 1, 1, type);
	}

	//Knight Checks
	if (!checked)
	{
		//checking if there is a knight of oppsite color
		//top right
		checked = board->getPiece(placeInd[1] + 2, placeInd[0] + 1) && board->getPiece(placeInd[1] + 2, placeInd[0] + 1)->getType() == ('n' - 32 * (bool)!type);
		checked = checked || board->getPiece(placeInd[1] + 1, placeInd[0] + 2) && board->getPiece(placeInd[1] + 1, placeInd[0] + 2)->getType() == ('n' - 32 * (bool)!type);

		//bot right
		checked = checked || board->getPiece(placeInd[1] - 2, placeInd[0] + 1) && board->getPiece(placeInd[1] - 2, placeInd[0] + 1)->getType() == ('n' - 32 * (bool)!type);
		checked = checked || board->getPiece(placeInd[1] - 1, placeInd[0] + 2) && board->getPiece(placeInd[1] - 1, placeInd[0] + 2)->getType() == ('n' - 32 * (bool)!type);

		//bot left
		checked = checked || board->getPiece(placeInd[1] - 2, placeInd[0] - 1) && board->getPiece(placeInd[1] - 2, placeInd[0] - 1)->getType() == ('n' - 32 * (bool)!type);
		checked = checked || board->getPiece(placeInd[1] - 1, placeInd[0] - 2) && board->getPiece(placeInd[1] - 1, placeInd[0] - 2)->getType() == ('n' - 32 * (bool)!type);

		//top left
		checked = checked || board->getPiece(placeInd[1] + 2, placeInd[0] - 1) && board->getPiece(placeInd[1] + 2, placeInd[0] - 1)->getType() == ('n' - 32 * (bool)!type);
		checked = checked || board->getPiece(placeInd[1] + 1, placeInd[0] - 2) && board->getPiece(placeInd[1] + 1, placeInd[0] - 2)->getType() == ('n' - 32 * (bool)!type);
	}

	//Pawn Checks
	if (!checked)
	{
		pawnCheck = type ? 1 : -1;
		checked = board->getPiece(placeInd[1] + pawnCheck, placeInd[0] + 1) && board->getPiece(placeInd[1] + pawnCheck, placeInd[0] + 1)->getType() == ('p' - 32 * (bool)!type);//pawn of opposite type
		checked = checked || board->getPiece(placeInd[1] + pawnCheck, placeInd[0] - 1) && board->getPiece(placeInd[1] + pawnCheck, placeInd[0] - 1)->getType() == ('p' - 32 * (bool)!type);//pawn of opposite type
	}

	//King Checks
	if (!checked)
	{
		//right
		checked = board->getPiece(placeInd[1] + 1, placeInd[0] + 1) && board->getPiece(placeInd[1] + 1, placeInd[0] + 1)->getType() == ('k' - 32 * (bool)!type);
		checked = checked || board->getPiece(placeInd[1], placeInd[0] + 1) && board->getPiece(placeInd[1], placeInd[0] + 1)->getType() == ('k' - 32 * (bool)!type);
		checked = checked || board->getPiece(placeInd[1] - 1, placeInd[0] + 1) && board->getPiece(placeInd[1] - 1, placeInd[0] + 1)->getType() == ('k' - 32 * (bool)!type);

		//left
		checked = checked || board->getPiece(placeInd[1] - 1, placeInd[0] - 1) && board->getPiece(placeInd[1] - 1, placeInd[0] - 1)->getType() == ('k' - 32 * (bool)!type);
		checked = checked || board->getPiece(placeInd[1], placeInd[0] - 1) && board->getPiece(placeInd[1], placeInd[0] - 1)->getType() == ('k' - 32 * (bool)!type);
		checked = checked || board->getPiece(placeInd[1] + 1, placeInd[0] - 1) && board->getPiece(placeInd[1] + 1, placeInd[0] - 1)->getType() == ('k' - 32 * (bool)!type);

		//mid
		checked = checked || board->getPiece(placeInd[1] + 1, placeInd[0]) && board->getPiece(placeInd[1] + 1, placeInd[0])->getType() == ('k' - 32 * (bool)!type);
		checked = checked || board->getPiece(placeInd[1] - 1, placeInd[0]) && board->getPiece(placeInd[1] - 1, placeInd[0])->getType() == ('k' - 32 * (bool)!type);
	}

	return checked;
}