#include "Fruit.h"

/*The function randomly sets fruit on board*/
void Fruit::SetFruit(const Board& board)
{
	srand(time(NULL));
	value = 5 + (rand() % 5);
	do
	{
		x = rand() % board.getLogRow();
		y = rand() % board.getLogCol();
	} while (board.getFromBoard(x, y) != Board::object::Breadcrumbs && board.getFromBoard(x, y) != Board::object::Empty);
}

/*The function moves a fruit on board, using GameObject move function*/
void Fruit::Move(Board& board, GameObject object)
{
	//Sleep(400);
	int lastStepX = x;
	int lastStepY = y;
	
	if(disappears==0 && delay==0)
			SetFruit(board);
	if (disappears == MaxFruitMoves)
	{
		if (delay == DelayFruit)
		{
			setDelay(0);
			setDisappears(0);
		}
		else
			delay++;
	}
	else
		disappears++;

	if (count5Moves == 5)
	{
		MoveToRandomDirection();
		count5Moves = 0;
	}
	else
		count5Moves++;

	GameObject::Move(board);
	if (board.getFromBoard(x, y) == Board::object::Tunnel)
	{
		x = lastStepX;
		y = lastStepY;
	}
	
	gotoxy(lastStepY, lastStepX);
	board.printObject(board.getFromBoard(lastStepX, lastStepY));
	gotoxy(y,x);
	if (board.getColor() == true)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	cout << value;
}
