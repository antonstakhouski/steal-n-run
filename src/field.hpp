#pragma once

#include <vector>

class Painter;

class Field
{
public:
	enum { WIDTH = 26, HEIGHT = 16 };
	enum { BLOCK_WIDTH = 40, BLOCK_HEIGHT = 40 };
	int step = 15;
	Field();
	enum Type { EMPTY, BRICK, CONCRETE, LADDER, GOLD, PLAYER ,ENEMY, POLE, BRICK2, LADDER2 };
	void setBlock(Type type, int x, int y);
	Type getBlock(int x, int y) const;
	void draw(Painter &);
	void drawBlock(int x, int y, Painter &, int*);
	int playerX;
	int playerY;
	int goldRemain;
	static int level;
	std::vector<int> xvec;
	std::vector<int> yvec;
private:
	//blocks coordinates
	int brick[2] 	= { 0,  0};
	int concrete[2] = {brick[0] + step + 1, 0};
	int ladder[2] 	= {32, 0};
	int pole[2]		= {48, 0};
	int gold[2]		= {96, 0};
	int enemy[2] 	= {gold[0] + step + 1, 0};
	int player[2] 	= {enemy[0] + step + 1, 0};
/*	int brick[2] 	= { 0,  0};
	int concrete[2] = {16, 0};
	int ladder[2] 	= {32 , 0};
	int pole[2]		= {ladder[0] + step, 0};
	int gold[2]		= {96, 0};
	int enemy[2] 	= {gold[0] + step + 1, 0};
	int player[2] 	= {enemy[0] + step + 1, 0};*/
	Type m_[HEIGHT][WIDTH];
};
