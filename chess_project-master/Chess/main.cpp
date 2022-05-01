#include "Board.h"
#include "Pipe.h"
#include <thread>

int main()
{	
	//Pipe
	srand(time_t(NULL));
	Pipe p;
	bool isConnect = p.connect();
	std::string response = "";
	std::string msgFromGraphics = "";
	char msgToGraphics[1024];
	char moveRet[2] = { 0 };

	Board* b;
	std::string move = "";
	int moveReturn = 0;

	//testing pipe
	while (!isConnect)
	{
		std::cout << "cant connect to graphics" << std::endl;
		std::cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << std::endl;
		std::cin >> response;

		if (response == "0")
		{
			std::cout << "trying connect again.." << std::endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return 0;
		}
	}




	try {
		b = new Board("rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0");
		strcpy_s(msgToGraphics, "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0");
		p.sendMessageToGraphics(msgToGraphics);
		msgFromGraphics = p.getMessageFromGraphics();

		while (msgFromGraphics != "quit")
		{
			b->print();
			move = msgFromGraphics;
			//std::cout << (b->getTurn() ? "White" : "Black") << "'s Turn\n";
			//std::cout << "Enter move: ";
			//std::getline(std::cin, move);

			if (0 <= move[0] - 'a' && move[0] - 'a' < BOARD_SIZE && 0 <= move[1] - '0' - 1 && move[1] - '0' - 1 < BOARD_SIZE)//checking if source indexes are good indexes
			{
				if (b->getBoard()[move[1] - '0' - 1][move[0] - 'a'])
				{
					if (b->getTurn() == (bool)isupper((b->getBoard()[move[1] - '0' - 1][move[0] - 'a'])->getType()))//if a piece exists in the source, and its the same type as the current piece to move.
					{
						moveReturn = b->getBoard()[move[1] - '0' - 1][move[0] - 'a']->move(b, move);
						if (moveReturn == 0 || moveReturn == 1 || moveReturn == 8 || moveReturn == 9)//if move was valid, next player's turn.
						{
							b->setTurn(!b->getTurn());//flipping turn
							//std::cout << b->getKings()[0] << ", 1:"<<b->getKings()[1] << "\n";
						}
						if (moveReturn == 1)
						{
							std::cout << "Check!\n";
						}
						else if (moveReturn == 4) {
							std::cout << "King in Check!\n";
						}
					}
					else
					{
						moveReturn = 2;
					}
				}
				else
				{
					moveReturn = 2;
				}
			}
			else
			{
				moveReturn = 5;
			}
			
			moveRet[0] = '0' + moveReturn;
			strcpy_s(msgToGraphics, moveRet); // msgToGraphics should contain the result of the operation


			// return result to graphics		
			p.sendMessageToGraphics(msgToGraphics);

			// get message from graphics
			msgFromGraphics = p.getMessageFromGraphics();
		}
		p.close();

	}
	catch (std::string excep)
	{
		std::cout << "Error: " << excep;
	}
	return 0;
}

/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project,
in order to read and write information from and to the Backend
*/


