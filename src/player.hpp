#pragma once
#include <list>
#include "field.hpp"

#define trapNum 3
#define trapUpdate 15

class Field;

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
	bool tick(Field &);
	void keyEvent(Action);
	void updateBlocks(Field &field);
	void testMovement(Field &field);
	void setTrap(Field &field);
private:
	Action action_;
	bool updateFlag;
	int playerX;
	int playerY;
	int oldX;
	int oldY;
	int testX;
	int testY;
	Field::Type oldBlockType;
	Field::Type testBlockType;
	struct digData trap[trapNum];
	int trapIterator;
};