#include "Board.h"

/* The function prints the board.*/
void Board::printBoardGame() const
{
	for (int i = 0; i < logRow; i++)
	{
		for (int j = 0; j < logCol; j++)
			printObject(this->board[i][j]);
		cout << endl;
	}
}

/* The function prints an object.*/
void Board::printObject(object ob) const
{
	switch (ob)
	{
	case (object::Breadcrumbs):
	{
		if (color == true)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
		cout << '.';
		break;
	}
	case (object::Wall):
	{
		if (color == true)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		cout << '#';
		break;
	}
	case (object::Empty):
	case (object::Tunnel):
	case (object::BlockCell):
	case (object::PointsLives):
		cout << ' ';
		break;
	case (object::Pacman):
		if (color == true)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		cout << '@';
		break;
	case (object::Ghost):
		if (color == true)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << '$';
		break;
	}
}

/*The function check if opening file is succeeded*/
void Board::checkFile(ifstream& infile)
{
if (!infile)
	{
		system("cls");
		cout << "Error. The file isn't exist !" << endl;
		exit(-1);
	}
}

/*The function gets a file name and puts it into a board game*/
void Board::getBoardFromFile(const char* fileName)
{
	string str;
	int row = 0, col, i, j, startRow;

	ifstream infile(fileName);
	checkFile(infile);

	getline(infile, str);

	if (str.at(0) == '&')
	{
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 20; j++)
				board[i][j] = object::PointsLives;
		}
		row = 3;
		getline(infile, str);
		getline(infile, str);
		getline(infile, str);
	}
	logCol = str.size();
	startRow = row;

	for (; row < ROW && (!infile.eof()); row++)
	{
		for (col = 0; col < str.size(); col++)
		{
			if (!(board[row][col] == object::PointsLives))
			{
				switch (str.at(col))
				{
				case '#':
					board[row][col] = object::Wall;
					break;
				case '@':
				
					board[row][col] = object::Pacman;
					break;
				case '$':
					board[row][col] = object::Ghost;
					break;
				case ' ':
				{
					if (col == 0 || col == logCol - 1 || row == startRow)
						board[row][col] = object::Tunnel;
					else
						board[row][col] = object::Breadcrumbs;
					break;
				}
				case '%':
					board[row][col] = object::BlockCell;
					break;
				case '&':
				{
					for (i = row; i < row + 3; i++)
					{
						for (j = col; j < col + 20; j++)
							board[i][j] = object::PointsLives;
					}
					break;
				}
				}
			}
		}
		getline(infile, str);
	}
	logRow = row ;

	col = 0;
	if (board[logRow - 1][0] == object::PointsLives)
		i = 3;
	else
		i = 0;

	while (col < logCol)
	{
		if (board[logRow - 1 - i][col] == object::Breadcrumbs)
			board[logRow - 1 - i][col] = object::Tunnel;
		col++;
	}
	infile.close();
}