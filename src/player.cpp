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
  if (field.getBlock(testX, testY) != Field::BRICK || 
    field.getBlock(testX, testY - 1) == Field::LADDER)
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

bool Player::tick(Field &field, std::vector<Enemy> &enemies)
{
    //close trap
  for (trapIterator = 0; trapIterator < trapNum; trapIterator++){
    //reduce remainTime
    if (Player::trap[trapIterator].timeRemain > 0)
      Player::trap[trapIterator].timeRemain--;

    //if is goin to close
    if (Player::trap[trapIterator].timeRemain == 0){
    //player is in a trap
      Player::trap[trapIterator].timeRemain--;
      if (playerX == trap[trapIterator].x && 
        playerY == trap[trapIterator].y)
        return false;

      //search for enemies
      for(unsigned int i = 0; i < enemies.size();i++){
        if (enemies[i].enemyX == trap[trapIterator].x && 
          enemies[i].enemyY == trap[trapIterator].y)
        {
          //fix this in future
          //cause this this can be LADDER
          //or enemy can be on the top of the trap
          enemies[i].updateFlag = false;
          field.setBlock(Field::BRICK, trap[trapIterator].x, 
            trap[trapIterator].y);
          enemies[i].oldBlockType = Field::EMPTY;
          enemies[i].enemyY--;
          enemies[i].oldX = enemies[i].enemyX;
          enemies[i].oldY = enemies[i].enemyY;
          field.setBlock(Field::ENEMY, enemies[i].enemyX, 
            enemies[i].enemyY);
          enemies[i].updateFlag = true;
          goto retToTrapCheck;
        }
      }

      //if trap is empty
      field.setBlock(Field::BRICK, trap[trapIterator].x, 
        trap[trapIterator].y);   
    }
    retToTrapCheck:
    (void)trapIterator;
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
  testBlockType = field.getBlock(playerX, playerY + 1);
  if (
    (
      testBlockType == Field::EMPTY ||
      testBlockType == Field::BRICK2 ||
      testBlockType == Field::LADDER2 ||
      testBlockType == Field::POLE ||
      testBlockType == Field::GOLD) && 
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
