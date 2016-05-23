#include "player.hpp"
//#include "field.hpp"
#include <cstdlib>

Player::Player(Field &field)
{
  //remember start player pos
  updateFlag = false;
  playerX = field.playerX;
  playerY = field.playerY;
  //data backup to restore after movement from this block
  oldX = playerX;
  oldY = playerY;
  oldBlockType = Field::EMPTY;
}

void Player::updateBlocks(Field &field)
{
  field.setBlock(oldBlockType, oldX, oldY);
  oldBlockType = field.getBlock(playerX, playerY);
  oldX = playerX;
  oldY = playerY;
  field.setBlock(Field::PLAYER, playerX, playerY);
}

void Player::keyEvent(Direction d)
{
  direction_ = d;
  updateFlag = true;
}

bool Player::tick(Field &field)
{
  if (updateFlag == true){
    switch (direction_)
    {
      case LEFT:
      playerX--;
      updateBlocks(field);
      break;
      case UP:
      playerY--;
      updateBlocks(field);
      break;
      case RIGHT:
      playerX++;
      updateBlocks(field);
      break;
      case DOWN:
      playerY++;
      updateBlocks(field);
      break;
    }
    updateFlag = false;
  }
  return true;    
}
  /*std::pair<int, int> p = blocks_.front();
  if (p.first < 0 || 
    p.first >= Field::WIDTH ||
    p.second < 0 || 
    p.second >= Field::HEIGHT)
    return false;
  if (field.block(p.first, p.second) == 
    Field::PLAYER)
    return false;
  blocks_.push_front(p);*/
/*  if (field.block(p.first, p.second) != 
      Field::FRUIT)
  {*/
     /* field.setBlock(Field::PLAYER, p.first, p.second);
      p = blocks_.back();
      field.setBlock(field.m_[p.second][p.first], p.first, p.second);
      blocks_.pop_back();*/
  /*}
  else
  {
    field.setBlock(Field::Player_BLOCK, p.first, p.second);
    field.newFruit();
  }*/
    /*if (blocks_.size() >= Field::WIDTH * Field::HEIGHT - 1)
      return false;*/