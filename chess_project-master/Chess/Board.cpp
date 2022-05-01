#include "Board.h"
#include "Rook.h"
#include "King.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"

Board::Board(std::string base)
{
    if (base.length() == BOARD_SIZE * BOARD_SIZE + 1)
    {
        this->_board = std::vector<std::vector<Piece*>>(BOARD_SIZE, std::vector<Piece*>(BOARD_SIZE, NULL));
        this->_kings = std::vector<int>(4, 0);//enough space for 2 king location
        int i = 0;
        int j = 0;
        char currPiece = ' ';
        for (i = BOARD_SIZE; i > 0; i--)
        {
            for (j = 0; j < BOARD_SIZE; j++)
            {
                currPiece = base[(BOARD_SIZE - i) * BOARD_SIZE + j];
                switch (currPiece)
                {
                case '#':
                    this->_board[i - 1][j] = NULL;
                    break;
                case 'r': case 'R':
                    this->_board[i - 1][j] = new Rook(currPiece);
                    break;
                case 'k': 
                    this->_board[i - 1][j] = new King(currPiece);
                    this->_kings[2] = j;
                    this->_kings[3] = i - 1;
                    break;
                case 'K':
                    this->_board[i - 1][j] = new King(currPiece);
                    this->_kings[0] = j;
                    this->_kings[1] = i - 1;
                    break;
                case 'p': case 'P':
                    this->_board[i - 1][j] = new Pawn(currPiece);
                    break;
                case 'b': case 'B':
                    this->_board[i - 1][j] = new Bishop(currPiece);
                    break;
                case 'n': case 'N':
                    this->_board[i - 1][j] = new Knight(currPiece);
                    break;
                case 'q': case 'Q':
                    this->_board[i - 1][j] = new Queen(currPiece);
                    break;
                default:
                    //anything other than # or piece
                    throw std::string("Trying to initalize board with bad piece symbol.");
                }
            }
        }
        j = 0;
        this->_turn = base[(BOARD_SIZE - i) * BOARD_SIZE + j] == '0';
    }
    else
    {
        throw std::string("Bad board string given.");
    }
}


void Board::print() const
{
    int i = 0, j = 0;

    for (i = BOARD_SIZE; i > 0; i--)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if (!this->_board[i - 1][j])
            {
                std::cout << " # ";
            }
            else
            {
                std::cout << " " << this->_board[i - 1][j]->getType() << " ";
            }
        }
        std::cout << "\n";
    }
}


bool Board::getTurn() const
{
    return this->_turn;
}

void Board::setTurn(const bool turn)
{
    this->_turn = turn;
}


/*
Function that returns a pointer to the board(2d vector)
*/
std::vector<std::vector<Piece*>> Board::getBoard() const
{
    return this->_board;
}


/*
Function that sets the board's piece pointer in a given place.
Input:  letter(in index),
        number(index).
*/
void Board::setPiece(int number, int letter ,Piece* piece)
{
    this->_board[number][letter] = piece;
}

/*
Function that gets a piece pointer from the board in a specific place.
returns null if index is invalid or if space is empty
*/
Piece* Board::getPiece(int number, int letter)
{
    Piece* ret = NULL;
    if (number < BOARD_SIZE && number >= 0 && letter < BOARD_SIZE && letter >= 0)
    {
        ret = this->_board[number][letter];
    }
    return ret;
}


/*
Function that updates the kings location.
Input:  which king
        updated indexes
*/
void Board::updateKings(int type, int letter, int number)
{
    int inc = 0;
    if (!type) { inc = 2; }//if its black
    this->_kings[inc] = letter;
    this->_kings[inc + 1] = number;
}

/*
Function that returns the kings vector
*/
std::vector<int> Board::getKing(int type)
{
    int inc = 0;
    std::vector<int> ret = std::vector<int>();
    if (!type) { inc = 2; }//if its black
    ret.push_back(_kings[inc]);
    ret.push_back(_kings[inc + 1]);
   
    return ret;
}