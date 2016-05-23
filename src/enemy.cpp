#include "enemy.hpp"
#include <cstdlib>

Enemy::Enemy(int x, int y)
{
	enemyX = x;
	enemyY = y;
	oldBlockType = Field::EMPTY;
	oldX = enemyX;
	oldY = enemyY;

	if(enemyX < Player::playerX)
		actionX_ = RIGHT;
	else
		actionX_ = LEFT;

	if(enemyY < Player::playerY)
		actionY_ = DOWN;
	else
		actionY_ = UP;
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
/*	if (testBlockType == Field::EMPTY)
		return false;*/
	testBlockType = field.getBlock(testX, testY);
	if (
		testBlockType == Field::BRICK ||
		testBlockType == Field::CONCRETE||
		testBlockType == Field::ENEMY
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
	//close trap
	for (trapIterator = 0; trapIterator < trapNum; trapIterator++){
		if (Player::trap[trapIterator].timeRemain > 0)
			Player::trap[trapIterator].timeRemain--;
		if (Player::trap[trapIterator].timeRemain == 0){
			if (field.getBlock(Player::trap[trapIterator].x,
				Player::trap[trapIterator].y) == Field::ENEMY &&
				enemyX != Player::trap[trapIterator].x &&
				enemyY != Player::trap[trapIterator].y)
				break;
			//if enemy is in a trap
			if (enemyX == Player::trap[trapIterator].x && 
				enemyY == Player::trap[trapIterator].y)
			{
				enemyY--;
				field.setBlock(Player::trap[trapIterator].oldBlockType,
					Player::trap[trapIterator].x, Player::trap[trapIterator].y);
				Player::trap[trapIterator].timeRemain--;
				//field.setBlock(Field::ENEMY, enemyX, enemyY);
			}
			
		}
	}

	//falling
	if (
		(
			field.getBlock(enemyX, enemyY + 1) == Field::EMPTY ||
			field.getBlock(enemyX, enemyY + 1) == Field::BRICK2 ||
			field.getBlock(enemyX, enemyY + 1) == Field::LADDER2) && 
		(oldBlockType != Field::POLE)
		)
	{
		testX = enemyX;
		testY = enemyY + 1;
		testMovement(field);
		return true;
	}

	testX = enemyX;
	testY = enemyY;

	//go to player quickly
	if (abs(Player::playerX - enemyX) <
		abs(Player::playerY - enemyY))
	{
		if (Player::playerX - enemyX >= 0)
			testX++;
		else
			testX--;

		testBlockType = field.getBlock(testX, testY);
		if (testBlockType == Field::PLAYER){
			return false;
		}

		//check testMove at first
		if (testMovement(field) == false){
			testX = enemyX;
			if (Player::playerY - enemyY >= 0){
				testY++;
			}
			else{
				testY--;
				if (
					(oldBlockType != Field::LADDER) &&
					(field.getBlock(testX, testY) == Field::EMPTY)
					)
					return true;
			}

			testBlockType = field.getBlock(testX, testY);
			if (testBlockType == Field::PLAYER){
				return false;
			}

			testMovement(field);
		}
		return true;
	}
	else
	{
		if (Player::playerY - enemyY >= 0){
			testY++;
		}
		else{
			testY--;
			testBlockType = field.getBlock(testX, testY);
			if (testBlockType == Field::PLAYER){
				return false;
			}
			if (
				(oldBlockType != Field::LADDER) &&
				(field.getBlock(testX, testY) == Field::EMPTY)
				)
				goto IFHIGH;
		}

		testBlockType = field.getBlock(testX, testY);
		if (testBlockType == Field::PLAYER){
			return false;
		}

		//check testMove at first
		if (testMovement(field) == false){
			IFHIGH:
			testY = enemyY;
			if (Player::playerX - enemyX >= 0)
				testX++;
			else
				testX--;

			testBlockType = field.getBlock(testX, testY);
			if (testBlockType == Field::PLAYER){
				return false;
			}

			testMovement(field);
		}
		return true;
	}
}
