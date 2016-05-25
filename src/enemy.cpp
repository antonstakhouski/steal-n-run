#include "enemy.hpp"
#include <cstdlib>

Enemy::~Enemy(){}

Enemy::Enemy(int xVal, int yVal)
{
	setX(xVal);
	setY(yVal);
	setOldBlockType(Field::EMPTY);
	setOldX(getX());
	setOldY(getY());
	setUpdateFlag(true);
}

bool Enemy::playerCatched(Field &field)
{
	setTestBlockType(field.getBlock(getTestX(), getTestY()));
	if (getTestBlockType() == Field::PLAYER){
		return true;
	}
	else
		return false;
}

bool Enemy::tick(Field &field, Player &player)
{
	if (getUpdateFlag() == false)
		return true;

	if (fallTest(field, Field::ENEMY) == true)
		return true;

	setTestX(getX());
	setTestY(getY());

	//go to player quickly
	if (abs(player.getX() - getX()) <
		abs(player.getY() - getY()))
	{
		if (player.getX() - getX() >= 0)
			setTestX(getTestX() + 1);
		else
			setTestX(getTestX() - 1);

		if(playerCatched(field) == true)
			return false;

		//check testMove at first
		if (testMovement(field, Field::ENEMY) == false){
			setTestX(getX());
			if (player.getY() - getY() >= 0){
				setTestY(getTestY() + 1);
			}
			else{
				setTestY(getTestY() - 1);
				if (jumpTest(field) == true)
					return true;
			}

			if(playerCatched(field) == true)
				return false;

			testMovement(field, Field::ENEMY);
		}
		return true;
	}
	else
	{
		if (player.getY() - getY() >= 0){
			setTestY(getTestY() + 1);
		}
		else{
			setTestY(getTestY() - 1);
			if(playerCatched(field) == true)
				return false;
			if (jumpTest(field) == true)
				goto IFHIGH;
		}

		if(playerCatched(field) == true)
			return false;

		//check testMove at first
		if (testMovement(field, Field::ENEMY) == false){
			IFHIGH:
			setTestY(getY());
			if (player.getX() - getX() >= 0)
				setTestX(getTestX() + 1);
			else
				setTestX(getTestX() - 1);

			if(playerCatched(field) == true)
				return false;

			testMovement(field, Field::ENEMY);
		}
		return true;
	}
}
