#pragma once

#include "field.hpp"
#include "player.hpp"

class Field;
class Player;

class Enemy
{
public:
	Enemy(int, int);
	void setEnemyX(int);
	void setEnemyY(int);
	bool tick(Field &);
	enum Action { LEFT, UP, RIGHT, DOWN };
	void updateBlocks(Field &field);
	bool testMovement(Field &field);
	void setOldBlockType();
private:
	Action actionX_;
	Action actionY_;
	int enemyX;
	int enemyY;
	int oldX;
	int oldY;
	int testX;
	int testY;
	Field::Type oldBlockType;
	Field::Type testBlockType;
};
