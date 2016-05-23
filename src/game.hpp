#pragma once
#include "player.hpp"
#include "enemy.hpp"
#include "field.hpp"
#include <vector>

class Painter;

class Game
{
public:
  void tick();
  void enemyTick();
  void draw(Painter &) const;
  void keyEvent(Player::Action);
  Game();
private:
  Field field_;
  Player player_;
  std::vector<Enemy> enemies;
};
