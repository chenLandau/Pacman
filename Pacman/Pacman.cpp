#include "Pacman.h"

Pacman:: Pacman(int x, int y, int direction, int currPoints, int currLives, int pointsOnBoardXPosition, int pointsOnBoardYPosition)
	:GameObject(x, y, direction)
{
	this->currPoints = currPoints; 
	this->currLives = currLives; 
	this->pointsOnBoardXPosition = pointsOnBoardXPosition;
	this->pointsOnBoardYPosition = pointsOnBoardYPosition;
}

/* The function checks if the player pressed direction.*/
bool Pacman::checkIfDirection(int direction)
{
	return((direction == RIGHT) || (direction == LEFT) || (direction == DOWN) || (direction == UP) || (direction == STAY) || (direction == right) || (direction == left) || (direction == down) || (direction == up) || (direction == stay));
}

/*The function moves the pacman on board, using GameObject move function*/
void Pacman::Move(Board& board,GameObject object)
{
	int lastStepX = x;
	int lastStepY = y;
	GameObject::Move(board,object);
	if (board.getFromBoard(x, y) == Board::object::Tunnel)
	{
		if (x == 0)
		{
			if (board.getFromBoard(board.getLogRow() - 1, y) == Board::object::Tunnel)
			x = board.getLogRow() - 1;
			else
			{
				x = lastStepX;
				y = lastStepY;
			}
		}
		else if (x == board.getLogRow() - 1)
		{
			if(board.getFromBoard(0, y) == Board::object::Tunnel)
			x = 0;
			else
			{
				x = lastStepX;
				y = lastStepY;
			}
		}
		if (y == 0)
		{
			if(board.getFromBoard(x, board.getLogCol() - 1) == Board::object::Tunnel)
			y = board.getLogCol() - 1;
			else
			{
				x = lastStepX;
				y = lastStepY;
			}
		}
		else if (y == board.getLogCol() - 1)
		{
			if(board.getFromBoard(x, 0) == Board::object::Tunnel)
			y = 0;
			else
			{
				x = lastStepX;
				y = lastStepY;
			}
		}
	}
	gotoxy(lastStepY, lastStepX);
	cout << ' ';
	if (board.getFromBoard(lastStepX, lastStepY) == Board::object::Pacman)
		board.setInBoard(lastStepX, lastStepY, Board::object::Empty);
	if (board.getFromBoard(lastStepX,lastStepY) == Board::object::Breadcrumbs) 
	{
		updatePointsOnBoard(board);
		board.setInBoard(lastStepX, lastStepY, Board::object::Empty);
	}

	gotoxy(y, x);
	if (board.getColor() == true)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	cout << "@";
}

/*The function add 1 point to the player, and updates it on the screen.*/
void Pacman::updatePointsOnBoard(Board& board, int value)
{
	currPoints+=value;
	gotoxy(pointsOnBoardYPosition, pointsOnBoardXPosition);
	if (board.getColor() == true)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	cout << currPoints;
}