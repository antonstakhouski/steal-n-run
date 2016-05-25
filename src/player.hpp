#pragma once

#include <vector>
#include "field.hpp"
#include "enemy.hpp"
#include "creature.hpp"

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

class Player : public Creature
{
public:
	~Player();
	enum Action { LEFT, UP, RIGHT, DOWN, DIGLEFT, DIGRIGHT};
	Player(Field &field);
	void deleteTrap();
	bool tick(Field &, std::vector<Enemy> &);
	void keyEvent(Action);
	void setTrap(Field &field);
	bool checkTraps(Field &, std::vector<Enemy> &);
private:
	struct digData* trap;
	Action action_;
	int trapIterator;
};
