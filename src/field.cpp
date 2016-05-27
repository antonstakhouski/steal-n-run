#include "field.hpp"
#include "painter.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int Field::level = 1;


Field::Field()
{
  goldRemain = 0;
  string command = "../lode_decode/decode ../lode_decode/loderun.dat ";
  command += char(level + '0');
  command += " > ../level_map";

  system(command.c_str());
  ifstream fin("../level_map");
  string str;
  char c;
  for (int y = 0; y < HEIGHT; ++y){
    getline(fin, str);
    if (str == "")
      break;
    for (int x = 0; x < WIDTH; ++x){
      c = str[x];
      if (c == 'L'){
        m_[y][x] = LADDER;
        continue;
      }
      if (c == 'C'){
       m_[y][x] = CONCRETE;
       continue;
     }
     if (c == 'B'){
      m_[y][x] = BRICK;
      continue;
    }
    if (c == 'E'){
      m_[y][x] = EMPTY;
      continue;
    }
    if (c == 'G'){
      m_[y][x] = GOLD;
      goldRemain++;
      continue;
    }
    if (c == '1'){
      m_[y][x] = LADDER2;
      continue;
    }
    if (c == '2'){
      m_[y][x] = BRICK2;
      continue;
    }
    if (c == '3'){
      m_[y][x] = POLE;
      continue;
    }
    if (c == 'P'){
      m_[y][x] = PLAYER;
      playerY = y;
      playerX = x;
      continue;
    }
    if (c == '4'){
      m_[y][x] = ENEMY;
      xvec.push_back(x);
      yvec.push_back(y);
      continue;
    }
  }
}
fin.close();
}

void Field::setBlock(Type type, int x, int y)
{
  m_[y][x] = type;
}

Field::Type Field::getBlock(int x, int y) const
{
  return m_[y][x];
}

void Field::drawBlock(int x, int y, Painter &p, int* startXY)
{
  p.square(x * BLOCK_WIDTH, y * BLOCK_HEIGHT,
    (x + 1) * BLOCK_WIDTH, (y + 1) * BLOCK_HEIGHT,
    startXY, step);
}

void Field::draw(Painter &p)
{
  for (int y = 0; y < HEIGHT; ++y){
    for (int x = 0; x < WIDTH; ++x){
      switch (m_[y][x]){

        case EMPTY:
        break;

        case LADDER2:
        break;

        case BRICK2:
        break;

        case LADDER:
        drawBlock(x, y, p, ladder);
        break;

        case CONCRETE:
        drawBlock(x, y, p, concrete);
        break;

        case BRICK:
        drawBlock(x, y, p, brick);
        break;

        case GOLD:
        drawBlock(x, y, p, gold);
        break;

        case POLE:
        drawBlock(x, y, p, pole);
        break;

        case PLAYER:
        drawBlock(x, y, p, player);
        break;

        case ENEMY:
        drawBlock(x, y, p, enemy);
        break;
      }
    }
  }
}
