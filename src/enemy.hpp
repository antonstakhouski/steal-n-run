#pragma once

#include "field.hpp"

class Field;

class Enemy
{
public:
	Enemy();
	void setEnemyX(int);
	void setEnemyY(int);
	bool tick(Field &);
	enum Action { LEFT, UP, RIGHT, DOWN };
	void updateBlocks(Field &field);
	bool testMovement(Field &field);
	void setOldBlockType();
private:
	Action action_;
	int enemyX;
	int enemyY;
	int oldX;
	int oldY;
	int testX;
	int testY;
	Field::Type oldBlockType;
	Field::Type testBlockType;
};
