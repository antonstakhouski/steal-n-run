#pragma once

#include "field.hpp"
#include "player.hpp"
#include "creature.hpp"

class Field;
class Player;

class Enemy : public Creature
{
public:
	Enemy(int, int);
	~Enemy();
	bool tick(Field &, Player &);
	void updateBlocks(Field &);
	bool playerCatched(Field &);
private:
};
