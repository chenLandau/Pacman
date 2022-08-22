#pragma once

#include "GameObject.h"

class Fruit : public GameObject
{
public:
	static const int MaxFruitMoves = 40;
	static const int DelayFruit = 10;

private:
	int value;
	int disappears;
	int delay;
	int count5Moves;

public:
	Fruit(int x, int y, int direction, int Value, int disappears, int delay, int count5Moves) : GameObject(x, y, direction) { this->value = Value; this->disappears = disappears; this->delay = delay;  this->count5Moves = count5Moves; }
	Fruit() : GameObject() {value = 0; disappears = 0; delay = 0; count5Moves = 0;}
	
	inline int getValue() const			{ return value; }
	inline int getDisappears() const { return disappears; }
	inline int getDelay() const { return delay; }

	inline void setValue(int Value)		{ this->value = Value; }
	inline void setDisappears(int disappears) { this->disappears = disappears; }
	inline void setDelay(int delay) { this->delay = delay; }

	void SetFruit(const Board& board);
	void Move(Board& board, GameObject object = GameObject(0, 0, 0)) override;
};
