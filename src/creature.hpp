#pragma once
#include "field.hpp"

class Field;

class Creature
{
public:
	Creature();
	virtual ~Creature() = 0;
	bool testMovement(Field &, Field::Type);
	bool fallTest(Field &, Field::Type);
	void updateBlocks(Field &, Field::Type);
	bool jumpTest(Field &);

	//getters
	int getX();
	int getY();
	bool getUpdateFlag();
	int getOldX();
	int getOldY();
	int getTestX();
	int getTestY();
	Field::Type getOldBlockType();
	Field::Type getTestBlockType();

	//setters
	void setX(int);
	void setY(int);
	void setUpdateFlag(bool);
	void setOldX(int);
	void setOldY(int);
	void setTestX(int);
	void setTestY(int);
	void setOldBlockType(Field::Type);
	void setTestBlockType(Field::Type);
private:
	int x;
	int y;
	bool updateFlag;
	int oldX;
	int oldY;
	int testX;
	int testY;
	Field::Type oldBlockType;
	Field::Type testBlockType;
};