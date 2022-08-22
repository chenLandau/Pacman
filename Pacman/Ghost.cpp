#include "Ghost.h"

Ghost::Ghost(int x, int y, int direction, GhostLevel level, int countSmartMove, int countRandomMove) 
	:GameObject(x, y, direction)
{ 
	this->smartLevel = level;
	this->countSmartMove = countSmartMove;
	this->countRandomMove = countRandomMove;
}

/*The function moves a ghost on board, using GameObject move function*/
void Ghost::Move(Board& board, GameObject object)
{
	//Sleep(400);
	int lastStepX = x;
	int lastStepY = y;
	GameObject::Move(board,object);
	
	if (board.getFromBoard(x, y) == Board::object::Tunnel)
	{
		x = lastStepX;
		y = lastStepY;
	}
	if (smartLevel == GhostLevel::Best)
	{
		ChasePacman(board,object);
	}
	else if (smartLevel == GhostLevel::Good)
	{
		if (countSmartMove == 20)
		{
			if (countRandomMove == 0)
			{
				MoveToRandomDirection();
				countRandomMove++;
			}
			else if (countRandomMove == 5)
			{
				setCountSmartMove(0);
				setCountRandomMove(0);
			}
			else
				countRandomMove++;
		}
		if (countSmartMove < 20)
		{
			ChasePacman(board, object);
			countSmartMove++;
		}
	}
	else
	{
		if (countSmartMove == 20)
		{
			setCountSmartMove(0);
			MoveToRandomDirection();
			countSmartMove++;
		}
		else
			countSmartMove++;
	}
	if (board.getFromBoard(lastStepX, lastStepY) == Board::object::Ghost)
		board.setInBoard(lastStepX, lastStepY, Board::object::Breadcrumbs);
	gotoxy(lastStepY, lastStepX);
	board.printObject(board.getFromBoard(lastStepX,lastStepY));
	gotoxy(y, x);
	if (board.getColor() == true)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cout << "$";
}

/*The function change the ghost move according to the position of pacman on the board*/
void Ghost::ChasePacman(const Board& board, GameObject Pacman)
{
	if (abs(x - Pacman.getX()) > abs(y - Pacman.getY()))
	{
		if (x < Pacman.getX() && board.getFromBoard(x + 1, y) != Board::object::Wall && board.getFromBoard(x + 1, y) != Board::object::BlockCell && board.getFromBoard(x + 1, y) != Board::object::PointsLives)
			direction = 'x';
		else if(x > Pacman.getX() && board.getFromBoard(x - 1, y) != Board::object::Wall && board.getFromBoard(x - 1, y) != Board::object::BlockCell && board.getFromBoard(x - 1, y) != Board::object::PointsLives)
			direction = 'w';
		else
		{
			if (y < Pacman.getY() && board.getFromBoard(x, y + 1) != Board::object::Wall && board.getFromBoard(x, y + 1) != Board::object::BlockCell && board.getFromBoard(x, y + 1) != Board::object::PointsLives)
				direction = 'd';
			else if (y > Pacman.getY() && board.getFromBoard(x, y - 1) != Board::object::Wall && board.getFromBoard(x, y - 1) != Board::object::BlockCell && board.getFromBoard(x, y - 1) != Board::object::PointsLives)
				direction = 'a';
		}
	}
	else
	{
		if (y < Pacman.getY() && board.getFromBoard(x, y + 1) != Board::object::Wall && board.getFromBoard(x, y + 1) != Board::object::BlockCell && board.getFromBoard(x, y + 1) != Board::object::PointsLives)
			direction = 'd';
		else if (y > Pacman.getY() && board.getFromBoard(x, y-1) != Board::object::Wall && board.getFromBoard(x, y - 1) != Board::object::BlockCell && board.getFromBoard(x, y - 1) != Board::object::PointsLives)
			direction = 'a';
		else
		{
			if (x < Pacman.getX() && board.getFromBoard(x+1, y) != Board::object::Wall && board.getFromBoard(x + 1, y) != Board::object::BlockCell && board.getFromBoard(x + 1, y) != Board::object::PointsLives)
				direction = 'x';
			else if (x > Pacman.getX() && board.getFromBoard(x-1, y) != Board::object::Wall && board.getFromBoard(x - 1, y) != Board::object::BlockCell && board.getFromBoard(x - 1, y) != Board::object::PointsLives)
				direction = 'w';
		}
	}
}
