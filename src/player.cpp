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
  if (oldBlockType == Field::GOLD){
    oldBlockType = Field::EMPTY;
    field.goldRemain--;
  }
  oldX = playerX;
  oldY = playerY;
  field.setBlock(Field::PLAYER, playerX, playerY);
}

void Player::keyEvent(Direction d)
{
  direction_ = d;
  updateFlag = true;
}

void Player::testMovement(Field &field)
{
  if (
    testX >= Field::WIDTH || testX < 0 ||
    testY >= Field::HEIGHT || testY < 0)
    return;

  testBlockType = field.getBlock(testX, testY);
  if (
    testBlockType == Field::BRICK ||
    testBlockType == Field::CONCRETE ||
    testBlockType == Field::ENEMY)
  {
    return;
  }
  else
  {
    playerX = testX;
    playerY = testY;
    updateBlocks(field);
    return;
  }
}

bool Player::tick(Field &field)
{
  //FIX: player can get stuck
  if (
    (
      field.getBlock(playerX, playerY + 1) == Field::EMPTY ||
      field.getBlock(playerX, playerY + 1) == Field::BRICK2 ||
      field.getBlock(playerX, playerY + 1) == Field::LADDER2) && 
    (oldBlockType != Field::POLE)
    )
  {
    updateFlag = false;
    testX = playerX;
    testY = playerY + 1;
    testMovement(field);
    return true;
  }

  if (updateFlag == true){
    updateFlag = false;
    switch (direction_)
    {
      case LEFT:
      testX = playerX;
      testY = playerY;
      testX = playerX - 1;
      testMovement(field);
      break;
      case UP:
      testX = playerX;
      testY = playerY;
      testY = playerY - 1;
      //"fly" and "jump" fix
      if (
        (oldBlockType != Field::LADDER) &&
        (field.getBlock(testX, testY) == Field::EMPTY)
        )
        return true;
      testMovement(field);
      break;
      case RIGHT:
      testX = playerX;
      testY = playerY;
      testX = playerX + 1;
      testMovement(field);
      break;
      case DOWN:
      testX = playerX;
      testY = playerY;
      testY = playerY + 1;
      testMovement(field);
      break;
    }
  }
  return true;    
}
