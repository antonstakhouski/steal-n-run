#pragma once

#include <vector>

class Painter;

class Field
{
public:
	enum { WIDTH = 26, HEIGHT = 16 };
	enum { BLOCK_WIDTH = 40, BLOCK_HEIGHT = 40 };
	Field();
	enum Type { EMPTY, BRICK, CONCRETE, LADDER, GOLD, PLAYER ,ENEMY, POLE, BRICK2, LADDER2 };
	void setBlock(Type type, int x, int y);
	Type getBlock(int x, int y) const;
	void draw(Painter &) const;
	int playerX;
	int playerY;
	int goldRemain;
	static int level;
	std::vector<int> xvec;
	std::vector<int> yvec;
private:
	Type m_[HEIGHT][WIDTH];
};
