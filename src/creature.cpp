#include "creature.hpp"

Creature::Creature(){}
Creature::~Creature(){}

bool Creature::testMovement(Field &field, Field::Type creatueType)
{
	if (
		testX >= Field::WIDTH || testX < 0 ||
		testY >= Field::HEIGHT || testY < 0)
		return false;

	testBlockType = field.getBlock(testX, testY);
	if (
		testBlockType == Field::BRICK ||
		testBlockType == Field::CONCRETE ||
		testBlockType == Field::ENEMY)
	{
		return false;
	}
	else
	{
		x = testX;
		y = testY;
		updateBlocks(field, creatueType);
		return true;
	}
}

bool Creature::fallTest(Field &field, Field::Type creatueType)
{
	testBlockType = field.getBlock(x, y + 1);
	if (
		(
			testBlockType == Field::EMPTY ||
			testBlockType == Field::BRICK2 ||
			testBlockType == Field::LADDER2 ||
			testBlockType == Field::POLE ||
			testBlockType == Field::GOLD) && 
		(oldBlockType != Field::POLE)
		)
	{
		testX = x;
		testY = y + 1;
		testMovement(field, creatueType);
		return true;
	}
	else
		return false;
}

void Creature::updateBlocks(Field &field, Field::Type creatueType)
{
	field.setBlock(oldBlockType, oldX, oldY);
	oldBlockType = field.getBlock(x, y);
	if (oldBlockType == Field::GOLD && 
		creatueType == Field::PLAYER)
	{
		oldBlockType = Field::EMPTY;
		field.goldRemain--;
	}
	oldX = x;
	oldY = y;
	field.setBlock(creatueType, x, y);
}

bool Creature::jumpTest(Field &field)
{
	//"fly" and "jump" fix
	if (
		(oldBlockType != Field::LADDER) &&
		(field.getBlock(testX, testY) == Field::EMPTY)
		)
		return true;
	else
		return false;
}

//------------------getters------------

int Creature::getX()
{
	return x;
}

int Creature::getY()
{
	return y;
}

int Creature::getOldX()
{
	return oldX;
}

int Creature::getOldY()
{
	return oldY;
}

bool Creature::getUpdateFlag()
{
	return updateFlag;
}

int Creature::getTestX()
{
	return testX;
}

int Creature::getTestY()
{
	return testY;
}

Field::Type Creature::getOldBlockType()
{
	return oldBlockType;
}

Field::Type Creature::getTestBlockType()
{
	return testBlockType;
}



//------------------setters------------

void Creature::setX(int value)
{
	x = value;
}

void Creature::setY(int value)
{
	y = value;
}

void Creature::setOldX(int value)
{
	oldX = value;
}

void Creature::setOldY(int value)
{
	oldY = value;
}

void Creature::setUpdateFlag(bool value)
{
	updateFlag = value;
}

void Creature::setTestX(int value)
{
	testX = value;
}

void Creature::setTestY(int value)
{
	testY = value;
}

void Creature::setOldBlockType(Field::Type value)
{
	oldBlockType = value;
}

void Creature::setTestBlockType(Field::Type value)
{
	testBlockType = value;
}
