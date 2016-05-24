#pragma once
#include "field.hpp"
#include <vector>
#include "enemy.hpp"

#define trapNum 3
#define trapUpdate 15

class Field;
class Enemy;

struct digData{
	int timeRemain;
	int x;
	int y;
	Field::Type oldBlockType;
};

class Player
{
public:
	enum Action { LEFT, UP, RIGHT, DOWN, DIGLEFT, DIGRIGHT};
	Player(Field &field);
	void deleteTrap();
	bool tick(Field &, std::vector<Enemy> &);
	void keyEvent(Action);
	void updateBlocks(Field &field);
	void testMovement(Field &field);
	void setTrap(Field &field);
	static int playerX;
	static int playerY;
	static struct digData* trap;
private:
	Action action_;
	bool updateFlag;
	int oldX;
	int oldY;
	int testX;
	int testY;
	Field::Type oldBlockType;
	Field::Type testBlockType;
	int trapIterator;
};
