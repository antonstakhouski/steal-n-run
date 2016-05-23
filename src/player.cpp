#include "player.hpp"

int Player::playerX = 0;
int Player::playerY = 0;
struct digData* Player::trap = 0;

Player::Player(Field &field)
{
  //remember start player pos
  trap = new digData[3];
  updateFlag = false;
  playerX = field.playerX;
  playerY = field.playerY;
  //data backup to restore after movement from this block
  oldX = playerX;
  oldY = playerY;
  oldBlockType = Field::EMPTY;
  for (int i = 0; i < trapNum; i++){
    trap[i].timeRemain = -1;
  }
}

void Player::deleteTrap()
{
  delete [] trap;
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

void Player::keyEvent(Action d)
{
  action_ = d;
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

void Player::setTrap(Field &field)
{
  testY = playerY + 1;
  if (field.getBlock(testX, testY) != Field::BRICK)
    return;
  else{
    //find free trap
    for (trapIterator = 0; trapIterator < trapNum; trapIterator++){
      if (trap[trapIterator].timeRemain == -1)
        break;
    }
    //if all traps are busy
    if (trapIterator == trapNum)
      return;
    //set trap
    trap[trapIterator].timeRemain = trapUpdate;
    trap[trapIterator].oldBlockType = field.getBlock(testX, testY);
    trap[trapIterator].x = testX;
    trap[trapIterator].y = testY;
    field.setBlock(Field::EMPTY, testX, testY);
    return;
  }
}

bool Player::tick(Field &field)
{
  //close trap
  for (trapIterator = 0; trapIterator < trapNum; trapIterator++){
      //if player is in a trap
    if (playerX == trap[trapIterator].x && 
      playerY == trap[trapIterator].y)
      return false;
  }

  //jump to the next level
  if(field.goldRemain == 0 && 
    oldBlockType == Field::LADDER && 
    playerY == 0)
  {
    Field::level++;
    return false;
  }

  //falling
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
    switch (action_)
    {
      case DIGLEFT:
      testX = playerX - 1;
      setTrap(field);
      break;

      case DIGRIGHT:
      testX = playerX + 1;
      setTrap(field);
      break;

      case LEFT:
      testY = playerY;
      testX = playerX - 1;
      testMovement(field);
      break;

      case UP:
      testX = playerX;
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
      testY = playerY;
      testX = playerX + 1;
      testMovement(field);
      break;
      case DOWN:

      testX = playerX;
      testY = playerY + 1;
      testMovement(field);
      break;
    }
  }
  return true;    
}
