
#include "King.h"

King::King(char type) : Piece(type)
{}

King::~King() {}

int King:: move(Board* board, std::string move)
{
	int finalReturn = checkMove(board, move);
	Piece* temp = NULL;
	int moveIndices[4] = { move[0] - 'a', move[1] - '0' - 1,  move[2] - 'a', move[3] - '0' - 1};
	std::vector<int> position = std::vector<int> ();
	
	if (finalReturn != 10)//if we found that the move is not a castles
	{
		if (board->getPiece(moveIndices[3], moveIndices[2]))
		{
			// 3 the cell is occupied by an ally.
			if (isupper(board->getPiece(moveIndices[3], moveIndices[2])->getType()) == isupper(this->getType()))
			{
				finalReturn = 3;
			}
			// if there's and enemy on the cell.
			else
			{
				//delete the enemy(as it is going to be eaten)
				temp = (board->getPiece(moveIndices[3], moveIndices[2]));
			}
		}


		//If all checks didnt change finalReturn from 0, then the move is valid. Make move.
		if (!finalReturn)
		{
			board->setPiece(moveIndices[3], moveIndices[2], this);
			board->setPiece(moveIndices[1], moveIndices[0], NULL);

			position.push_back(moveIndices[2]);
			position.push_back(moveIndices[3]);

			if (moveUtil::checkThreat(board, position))//if the color's king is in check after moving
			{
				finalReturn = 4;
				board->setPiece(moveIndices[1], moveIndices[0], this);//restoring the piece
				board->setPiece(moveIndices[3], moveIndices[2], temp);//restoring the enemy
			}
			else
			{
				if (temp) { delete temp; }//deleting the enemy, if there was one

				board->updateKings(isupper(this->_type), moveIndices[2], moveIndices[3]);
				this->_hasMoved = true;
				//If after doing the move, opposite king is in check
				if (moveUtil::checkThreat(board, position))
				{
					finalReturn = 1;
				}
			}
		}
	}
	else
	{
		finalReturn = 8 + (bool)isupper(this->_type);//8==black castles, 9==white castles
		//move is castles
		if (moveIndices[2] - moveIndices[0] == 2)//if its to the right
		{
			//move king
			board->setPiece(moveIndices[3], moveIndices[2], this);
			board->setPiece(moveIndices[1], moveIndices[0], NULL);

			//move rook
			board->setPiece(moveIndices[3], moveIndices[2] - 1, board->getPiece(moveIndices[3], moveIndices[2] + 1));
			board->setPiece(moveIndices[3], moveIndices[2] + 1, NULL);

		}
		else
		{
			//move king
			board->setPiece(moveIndices[3], moveIndices[2], this);
			board->setPiece(moveIndices[1], moveIndices[0], NULL);

			//move rook
			board->setPiece(moveIndices[3], moveIndices[2] + 1, board->getPiece(moveIndices[3], moveIndices[2] - 2));
			board->setPiece(moveIndices[3], moveIndices[2] - 2, NULL);
		}

		board->updateKings(isupper(this->_type), moveIndices[2], moveIndices[3]);
		this->_hasMoved = true;
		
	}
	return finalReturn;
}

int King::checkMove(Board* board, std::string move)
{
	int finalReturn = 0;
	int moveIndices[4] = { move[0] - 'a', move[1] - '0' - 1,  move[2] - 'a', move[3] - '0' - 1 };

	std::vector<int> kingPlace = std::vector<int>();
	kingPlace.push_back(moveIndices[0]);
	kingPlace.push_back(moveIndices[1]);

	if (0 > moveIndices[0] || moveIndices[0] >= BOARD_SIZE || 0 > moveIndices[1] || moveIndices[1] >= BOARD_SIZE || 0 > moveIndices[2] || moveIndices[2] >= BOARD_SIZE || 0 > moveIndices[3] || moveIndices[3] >= BOARD_SIZE)
	{
		finalReturn = 5;//Bad Indices
	}
	
	//the king moves only up or down.
	if (moveIndices[0] == moveIndices[2])
	{
		// if the player tries to move more than one cell.
		if (abs(moveIndices[1] - moveIndices[3]) != 1)
		{
			finalReturn = 6;
		}
	}
	else
	{
		//Castles
		if (!this->_hasMoved && moveIndices[1] == moveIndices[3] && abs(moveIndices[2] - moveIndices[0]) == 2)//king not moved, trying to move 2 squares left/right
		{
			if (moveIndices[2] - moveIndices[0] == 2)//if its to the right
			{
				//if theres a rook of the same color
				if (board->getPiece(moveIndices[1], moveIndices[2] + 1) && board->getPiece(moveIndices[1], moveIndices[2] + 1)->getType() == ('r' - 32 * (bool)isupper(this->_type)))
				{
					if (!board->getPiece(moveIndices[1], moveIndices[2] + 1)->getHasMoved())//rook hasnt moved
					{
						if (!board->getPiece(moveIndices[1], moveIndices[0] + 1) && !board->getPiece(moveIndices[1], moveIndices[0] + 2))//no pieces between
						{
							if (!moveUtil::checkThreat(board, kingPlace))//if king is not currently checked
							{
								kingPlace[0]++;//emulating king move one to the right
								board->setPiece(moveIndices[1], moveIndices[0] + 1, this);
								board->setPiece(moveIndices[1], moveIndices[0], NULL);
								if (!moveUtil::checkThreat(board, kingPlace))
								{
									kingPlace[0]++;//emulating king move one more to the right
									board->setPiece(moveIndices[1], moveIndices[0] + 2, this);
									board->setPiece(moveIndices[1], moveIndices[0] + 1, NULL);
									if (!moveUtil::checkThreat(board, kingPlace))
									{
										finalReturn = 10;//using 10 to indicate castles has been made
									}
									board->setPiece(moveIndices[1], moveIndices[0], this);
									board->setPiece(kingPlace[1], kingPlace[0], NULL);
								}
								else
								{
									board->setPiece(moveIndices[1], moveIndices[0], this);
									board->setPiece(kingPlace[1], kingPlace[0], NULL);
								}
							}
						}
					}
				}
			}
			else//its to the left
			{
				//if theres a rook of the same color
				if (board->getPiece(moveIndices[1], moveIndices[2] - 2) && board->getPiece(moveIndices[1], moveIndices[2] - 2)->getType() == ('r' - 32 * (bool)isupper(this->_type)))
				{
					if (!board->getPiece(moveIndices[1], moveIndices[2] - 2)->getHasMoved())//rook hasnt moved
					{
						if (!board->getPiece(moveIndices[1], moveIndices[0] - 1) && !board->getPiece(moveIndices[1], moveIndices[0] - 2))//no pieces between
						{
							if (!moveUtil::checkThreat(board, kingPlace))//if king is not currently checked
							{
								kingPlace[0]--;//emulating king move one to the left
								board->setPiece(moveIndices[1], moveIndices[0] - 1, this);
								board->setPiece(moveIndices[1], moveIndices[0], NULL);
								if (!moveUtil::checkThreat(board, kingPlace))
								{
									kingPlace[0]--;//emulating king move one more to the left
									board->setPiece(moveIndices[1], moveIndices[0] - 2, this);
									board->setPiece(moveIndices[1], moveIndices[0] - 1, NULL);
									if (!moveUtil::checkThreat(board, kingPlace))
									{
										finalReturn = 10;//using 10 to indicate castles has been made
									}
									board->setPiece(moveIndices[1], moveIndices[0], this);
									board->setPiece(kingPlace[1], kingPlace[0], NULL);
								}
								else
								{
									board->setPiece(moveIndices[1], moveIndices[0], this);
									board->setPiece(kingPlace[1], kingPlace[0], NULL);
								}
							}
						}
					}
				}
			}

			if (finalReturn != 10)//if it was not a valid castles
			{
				finalReturn = 6;//bad move
			}
		}
		else if (moveIndices[1] != moveIndices[3] && moveIndices[0] != moveIndices[2] && abs(moveIndices[1] - moveIndices[3]) + abs(moveIndices[0] - moveIndices[2]) != 2)//if the king moves more than one cell diagonally
		{
			finalReturn = 6;
		}
	}


	if(move.substr(0,2) == move.substr(2,2))
	{
		finalReturn = 7;
	}
	return finalReturn;
}



