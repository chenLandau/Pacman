#include "Game.h"

/* The function prints the main menu.*/
void Game::printMenu()
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << "#####################################" << endl;
	cout << "# Menu:                             #" << endl;
	cout << "# (1) Start a new game              #" << endl;
	cout << "# (8) Present instructions and keys #" << endl;
	cout << "# (9) Exit                          #" << endl;
	cout << "#####################################" << endl;
}

/* The function prints the instructions.*/
void Game::printInstructions()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << "#################################################################" << endl;
	cout << "# Keys:                                                         #" << endl;
	cout << "# LEFT a or A                                                   #" << endl;
	cout << "# RIGHT d or D                                                  #" << endl;
	cout << "# UP w or W                                                     #" << endl;
	cout << "# Down x or X                                                   #" << endl;
	cout << "# STAY s or S                                                   #" << endl;
	cout << "#                                                               #" << endl;
	cout << "# Instructions:                                                 #" << endl;
	cout << "# The pacman should travel on screen and eats the breadcrumbs.  #" << endl;
	cout << "# Each eaten breadcrumb equals a point to be earned.            #" << endl;
	cout << "# Once all breadcrumbs on screen are eaten the game ends.       #" << endl;
	cout << "# In case a ghost eats the pacman, you lose a live.             #" << endl;
	cout << "# If you lose 3 lives, the game is over.                        #" << endl;
	cout << "#                                                               #" << endl;
	cout << "# Please press any key for the menu.                            #" << endl;
	cout << "#################################################################" << endl;
}

/*The function reset all objects game*/
void Game::setObjects()
{
	bool pointslives = true;

	for (int i = 0; i < board.getLogRow(); i++)
	{
		for (int j = 0; j < board.getLogCol(); j++)
		{
			if (board.getFromBoard(i, j) == Board::object::Pacman)
			{
				pacman.setX(i);
				pacman.setY(j);
			}
			else if (board.getFromBoard(i, j) == Board::object::Ghost)
				ghostArr.push_back(Ghost(i, j, 0, Ghost::GhostLevel::Best, 0, 0));//fix

			else if (board.getFromBoard(i, j) == Board::object::PointsLives)
			{
				if (pointslives)
				{
					pacman.setpointXPositions(i);
					pacman.setpointYPosition(j + 9);
					pacman.gotoxy(j, i);
					cout << " Points: " << pacman.getCurrPoints();
					pacman.gotoxy(j, i + 1);
					cout << " Lives: " << pacman.getCurrLives();
					pacman.gotoxy(90, 25);//check if need
					pointslives = false;
				}
			}
		}
	}
}

/* The function moves the ghosts and the pacman on the board.*/
void Game::moveObjects()
{
	int direction = _getch();
	int tmpDirection = direction;

	while (!checkIfWin())
	{
		Sleep(200);
		if (_kbhit())
			tmpDirection = _getch();
		if (pacman.checkIfDirection(tmpDirection))
		{
			direction = tmpDirection;
			pacman.setDirection(direction);
		}
		if (tmpDirection == ESC)
		{
			do
			{
				MessageBox(NULL, TEXT("Game paused, press ESC again to continue."), TEXT("Game paused"), MB_OK);
				tmpDirection = _getch();
			}

			while (tmpDirection != ESC);
		}
		tmpDirection = 0;
		pacman.Move(board);
		MoveGhosts();
		fruit.Move(board);
		
		if (pacman == fruit)
		{
			pacman.updatePointsOnBoard(board,fruit.getValue());
			fruit.setDisappears(Fruit::MaxFruitMoves);
			fruit.gotoxy(fruit.getY(), fruit.getX());
			board.printObject(board.getFromBoard(fruit.getX(), fruit.getY()));
		}
		if (checkIfGhost())
			return;
	}
	return;
}

/*The function move ghosts on board*/
void Game::MoveGhosts()
{
	for (int i = 0; i < ghostArr.size(); i++)
		ghostArr.at(i).Move(board, pacman);
}

/* The function checks if the pacman and the ghost in the same location.*/
bool Game::checkIfGhost()
{
	for (int i = 0; i < ghostArr.size(); i++)
	{
		if (pacman == ghostArr.at(i))
			return true;
		if (fruit == ghostArr.at(i))
		{
			fruit.gotoxy(fruit.getY(), fruit.getX());
			board.printObject(board.getFromBoard(fruit.getX(), fruit.getY()));
			fruit.setDisappears(Fruit::MaxFruitMoves);
		}
	}
	return false;
}

/* The function prints win message.*/
void Game::winGame()
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << "######################################" << endl;
	cout << "# You won !                          #" << endl;
	cout << "# Please press any key for the menu. #" << endl;
	cout << "######################################" << endl;
}

/* The function prints lose message.*/
void Game::loseGame()
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << "######################################" << endl;
	cout << "# Game Over !                        #" << endl;
	cout << "# Please press any key for the menu. #" << endl;
	cout << "######################################" << endl;
}

/*The function checks if pacman ate all the breadcrumbs on board*/
bool Game::checkIfWin()
{
	for (int i = 0; i < board.getLogRow(); i++)
	{
		for (int j = 0; j < board.getLogCol(); j++)
		{
			if (board.getFromBoard(i, j) == Board::object::Breadcrumbs)
				return false;
		}
	}
	return true;
}

/*The function play the game in one board file*/
bool Game::playInSingleFile(const char* fileName)
{
	//board.getBoardFromFile("check.txt");
	board.getBoardFromFile(fileName);

	while (pacman.getCurrLives() > 0)
	{
		system("cls");
		board.printBoardGame();
		setObjects();
		moveObjects();
		if (checkIfWin())
		{
			return true;
		}
		pacman.setCurrLives(pacman.getCurrLives() - 1);
	}
	return false;
}

/*The function checks if the user wants to plat with colors or not*/
void Game::checkColors()
{
	int tmp;
	system("cls");
	cout << "######################################################" << endl;
	cout << "# If you want to play without colors please enter 1. #" << endl << "# Else press any key.                                #" << endl;
	cout << "######################################################" << endl;
	tmp = _getch();
	if (tmp == '1')
	{
		color = false;
		board.setColor(false);
	}
}

/*The function checks the ghost level the user wants to play with*/
void Game::checkGhostLevel()
{
	int tmp;
	system("cls");
	cout << "######################################################" << endl;
	cout << "#Choose ghost level:                                 #" << endl;
	cout << "#(1) BEST                                            #" << endl;
	cout << "#(2) GOOD                                            #" << endl;
	cout << "#(3) NOVICE                                          #" << endl;
	cout << "######################################################" << endl;
	cin >> tmp;

	switch (tmp)
	{
	case 1:
	{
		for (int i = 0; i < ghostArr.size(); i++)
			ghostArr.at(i).setSmartLevel(Ghost::GhostLevel::Best);
		break;
	}
	case 2:
	{
		for (int i = 0; i < ghostArr.size(); i++)
			ghostArr.at(i).setSmartLevel(Ghost::GhostLevel::Good);
		break;

	}
	case 3:
	{
		for (int i = 0; i < ghostArr.size(); i++)
			ghostArr.at(i).setSmartLevel(Ghost::GhostLevel::Novice);
		break;

	}
	default:
	{
		cout << "Wrong Input! The ghosts will be novice" << endl;
		for (int i = 0; i < ghostArr.size(); i++)
			ghostArr.at(i).setSmartLevel(Ghost::GhostLevel::Novice);
		break;
	}
	}
}

/* The function uses the game functions until the player win or lose.*/
void Game::playGame()
{
	playInSingleFile("check.txt");
	//running on 3 files
	//winGame();
	//loseGame();
}

/* The function prints the menu and start the game.*/
void Game::startGame()
{
	bool condition = true;
	int choice,tmp;

	while (condition)
	{
		printMenu();
		cin >> choice;

		switch (choice)
		{
			case 1:
			{

				checkColors();
				checkGhostLevel();
				playGame();
				tmp = _getch();
				break;
			}
			case 8:
			{
				system("cls");
				printInstructions();
				tmp = _getch();
				break;
			}
			case 9:
				exit(1);
			default:
			{
				system("cls");
				cout << "######################################################" << endl;
				cout << "# Wrong input.                                       #" << endl;
				cout << "# Please press any key for the menu.                 #" << endl;
				cout << "######################################################" << endl;
				tmp = _getch();
				break;
			}
		}

	}
}























































