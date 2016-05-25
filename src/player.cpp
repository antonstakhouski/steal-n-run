#include "player.hpp"

Player::~Player(){}

Player::Player(Field &field)
{
  //remember start player pos
  trap = new digData[3];
  setUpdateFlag(false);
  setX(field.playerX);
  setY(field.playerY);
  //data backup to restore after movement from this block
  setOldX(getX());
  setOldY(getY());
  setOldBlockType(Field::EMPTY);
  for (int i = 0; i < trapNum; i++){
    trap[i].timeRemain = -1;
  }
}

void Player::deleteTrap()
{
  delete [] trap;
}

void Player::keyEvent(Action d)
{
  action_ = d;
  setUpdateFlag(true);
}

void Player::setTrap(Field &field)
{
  setTestY(getY() + 1);
  if (field.getBlock(getTestX(), getTestY()) != Field::BRICK || 
    field.getBlock(getTestX(), getTestY() - 1) == Field::LADDER)
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
    trap[trapIterator].oldBlockType = field.getBlock(getTestX(), getTestY());
    trap[trapIterator].x = getTestX();
    trap[trapIterator].y = getTestY();
    field.setBlock(Field::EMPTY, getTestX(), getTestY());
    return;
  }
}

bool Player::checkTraps(Field &field, std::vector<Enemy> &enemies)
{
      //close trap
  for (trapIterator = 0; trapIterator < trapNum; trapIterator++){
    //reduce remainTime
    if (trap[trapIterator].timeRemain > 0)
      trap[trapIterator].timeRemain--;

    //if is goin to close
    if (trap[trapIterator].timeRemain == 0){
    //player is in a trap
      trap[trapIterator].timeRemain--;
      if (getX() == trap[trapIterator].x && 
        getY() == trap[trapIterator].y)
        return false;

      //search for enemies
      for(unsigned int i = 0; i < enemies.size();i++){
        if (enemies[i].getX() == trap[trapIterator].x && 
          enemies[i].getY() == trap[trapIterator].y)
        {
          //fix this in future
          //cause this this can be LADDER
          //or enemy can be on the top of the trap
          enemies[i].setUpdateFlag(false);
          field.setBlock(Field::BRICK, trap[trapIterator].x, 
            trap[trapIterator].y);
          enemies[i].setOldBlockType(Field::EMPTY);
          enemies[i].setY(enemies[i].getY() - 1);
          enemies[i].setOldX(enemies[i].getX());
          enemies[i].setOldY(enemies[i].getY());
          field.setBlock(Field::ENEMY, enemies[i].getX(), 
            enemies[i].getY());
          enemies[i].setUpdateFlag(true);
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
  return true;
}

bool Player::tick(Field &field, std::vector<Enemy> &enemies)
{
  if (checkTraps(field, enemies) == false)
    return false;

  //jump to the next level
  if(field.goldRemain == 0 && 
    getOldBlockType() == Field::LADDER && 
    getY() == 0)
  {
    Field::level++;
    return false;
  }

  if (fallTest(field, Field::PLAYER) == true)
    return true;

  if (getUpdateFlag() == true){
    setUpdateFlag(false);
    switch (action_)
    {
      case DIGLEFT:
      setTestX(getX() - 1);
      setTrap(field);
      break;

      case DIGRIGHT:
      setTestX(getX() + 1);
      setTrap(field);
      break;

      case LEFT:
      setTestY(getY());
      setTestX(getX() - 1);
      testMovement(field, Field::PLAYER);
      break;

      case UP:
      setTestX(getX());
      setTestY(getY() - 1);
      if (jumpTest(field) == true)
        return true;
      testMovement(field, Field::PLAYER);
      break;

      case RIGHT:
      setTestY(getY());
      setTestX(getX() + 1);
      testMovement(field, Field::PLAYER);
      break;

      case DOWN:
      setTestX(getX());
      setTestY(getY() + 1);
      testMovement(field, Field::PLAYER);
      break;
    }
  }
  return true;
}
