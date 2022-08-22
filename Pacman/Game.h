#pragma once

#include "Board.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"

#include <vector>
//#include <fstream>
//#include <Windows.h>
#include<iostream>
using namespace std;

class Game
{
public:
	static const int ESC = 27;
	
private:
	Board board;
	Pacman pacman;
	vector <Ghost> ghostArr;
	Fruit fruit;
	bool color = true;
	
public:
	void printMenu();
	void printInstructions();
	void setObjects();
	void moveObjects();
	void MoveGhosts();
	bool checkIfGhost();
	void winGame();
	void loseGame();
	bool checkIfWin();
	bool playInSingleFile(const char* fileName);
	void checkColors();
	void checkGhostLevel();
	void playGame();
	void startGame();
};

