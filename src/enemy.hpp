#pragma once

#include "field.hpp"
#include "player.hpp"

class Field;
class Player;

class Enemy
{
public:
	Enemy(int, int);
	bool tick(Field &);
	enum Action { LEFT, UP, RIGHT, DOWN };
	void updateBlocks(Field &field);
	bool testMovement(Field &field);
	Field::Type oldBlockType;
	int oldX;
	int oldY;
	int enemyX;
	int enemyY;
	bool updateFlag;
private:
	int testX;
	int testY;
	Field::Type testBlockType;
};
