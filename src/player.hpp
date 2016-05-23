#pragma once
#include <list>
#include "field.hpp"

class Field;

class Player
{
public:
	enum Direction { LEFT, UP, RIGHT, DOWN };
	Player(Field &field);
	bool tick(Field &);
	void keyEvent(Direction);
	void updateBlocks(Field &field);
	void testMovement(Field &field);
private:
	typedef std::list<std::pair<int, int> > Blocks;
	Blocks blocks_;
	Direction direction_;
	bool updateFlag;
	int playerX;
	int playerY;
	int oldX;
	int oldY;
	int testX;
	int testY;
	Field::Type oldBlockType;
	Field::Type testBlockType;
};