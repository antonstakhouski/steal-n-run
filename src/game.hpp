#pragma once
#include "player.hpp"
#include "enemy.hpp"
#include "field.hpp"
#include <vector>

class Painter;
class Player;
class Enemy;
class Field;

class Game
{
public:
  void tick();
  void enemyTick();
  void draw(Painter &);
  void keyEvent(Player::Action);
  Game();
private:
  Field field_;
  Player player_;
  std::vector<Enemy> enemies;
};
