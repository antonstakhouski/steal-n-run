#include "enemy.hpp"

void Enemy::setEnemyX(int x)
{
	enemyX = x;
}

void Enemy::setEnemyY(int y)
{
	enemyY = y;
}

Enemy::Enemy(int x, int y)
{
	enemyX = x;
	enemyY = y;
	oldBlockType = Field::EMPTY;
	oldX = enemyX;
	oldY = enemyY;
	actionX_ = LEFT;
	actionY_ = LEFT;
}

void Enemy::setOldBlockType()
{
	oldBlockType = Field::EMPTY;
	oldX = enemyX;
	oldY = enemyY;	
}

void Enemy::updateBlocks(Field &field)
{
	field.setBlock(oldBlockType, oldX, oldY);
	oldBlockType = field.getBlock(enemyX, enemyY);
	oldX = enemyX;
	oldY = enemyY;
	field.setBlock(Field::ENEMY, enemyX, enemyY);
}

bool Enemy::testMovement(Field &field)
{
	if (
		testX >= Field::WIDTH || testX < 0 ||
		testY >= Field::HEIGHT || testY < 0)
		return false;

	testBlockType = field.getBlock(testX, testY + 1);
	if (testBlockType == Field::EMPTY)
		return false;
	testBlockType = field.getBlock(testX, testY);
	if (
		testBlockType == Field::BRICK ||
		testBlockType == Field::CONCRETE
		)
	{
		return false;
	}
	else
	{
		enemyX = testX;
		enemyY = testY;
		updateBlocks(field);
		return true;
	}
}

bool Enemy::tick(Field &field)
{
/*	testX = enemyX;
	testY = enemyY;

	if (action_ == LEFT)
		testX--;
	if (action_ == RIGHT)
		testX++;

	//if enemy has reached player
	testBlockType = field.getBlock(testX, testY);
	if (testBlockType == Field::PLAYER){
		return false;
	}

	if (testMovement(field) == false){
		if (action_ == LEFT)
			action_ = RIGHT;
		else 
			action_ = LEFT;
	}*/
	return true;
}
