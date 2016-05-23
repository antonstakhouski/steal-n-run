#include "field.hpp"
#include "painter.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

Field::Field()
{
  level = 0;
  level++;
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

void Field::draw(Painter &p) const
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
        p.square(x * BLOCK_WIDTH, y * BLOCK_HEIGHT,
          (x + 1) * BLOCK_WIDTH, (y + 1) * BLOCK_HEIGHT,
          0, 1, 0);
        break;

        case CONCRETE:
        p.square(x * BLOCK_WIDTH, y * BLOCK_HEIGHT,
          (x + 1) * BLOCK_WIDTH, (y + 1) * BLOCK_HEIGHT,
          0.255, 0.128, 0);
        break;

        case BRICK:
        p.square(x * BLOCK_WIDTH, y * BLOCK_HEIGHT,
          (x + 1) * BLOCK_WIDTH, (y + 1) * BLOCK_HEIGHT,
          1, 0, 0);
        break;

        case GOLD:
        p.square(x * BLOCK_WIDTH, y * BLOCK_HEIGHT,
          (x + 1) * BLOCK_WIDTH, (y + 1) * BLOCK_HEIGHT,
          1, 1, 0);
        break;

        case POLE:
        p.square(x * BLOCK_WIDTH, y * BLOCK_HEIGHT,
          (x + 1) * BLOCK_WIDTH, (y + 1) * BLOCK_HEIGHT,
          1, 1, 1);
        break;

        case PLAYER:
        p.square(x * BLOCK_WIDTH, y * BLOCK_HEIGHT,
          (x + 1) * BLOCK_WIDTH, (y + 1) * BLOCK_HEIGHT,
          0, 0, 1);
        break;

        case ENEMY:
        p.square(x * BLOCK_WIDTH, y * BLOCK_HEIGHT,
          (x + 1) * BLOCK_WIDTH, (y + 1) * BLOCK_HEIGHT,
          0.1, 0.3, 0.4);
        break;
      }
    }
  }
}