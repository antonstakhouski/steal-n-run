#include "game.hpp"
#include "painter.hpp"
#include "field.hpp"
#include "player.hpp"
#include "enemy.hpp"

Game::Game():field_(), player_(field_){
	Enemy *enemy;
	for (unsigned int i = 0; i < field_.xvec.size(); i++){
		enemy = new Enemy(field_.xvec[i], field_.yvec[i]);
		enemies.push_back(*enemy);
		delete enemy;
	}
}

void Game::draw(Painter &p)
{
	field_.draw(p);
}

void Game::keyEvent(Player::Action d)
{
	player_.keyEvent(d);
}

void Game::enemyTick()
{
	for (unsigned int i = 0; i < field_.xvec.size(); i++){
		if(!enemies[i].tick(field_, player_)){
			enemies.clear();
			field_ = Field();
			Enemy *enemy;
			for (unsigned int i = 0; i < field_.xvec.size(); i++){
				enemy = new Enemy(field_.xvec[i], field_.yvec[i]);
				enemies.push_back(*enemy);
				delete enemy;
			}
			player_.deleteTrap();
			player_ = Player(field_);
			return;
		}
	}
}

void Game::tick()
{
	//stairway to heaven
	//no. it is just stairway to the next level
	if (field_.goldRemain == 0){
		for (int y = 0; y < Field::HEIGHT; ++y){
			for (int x = 0; x < Field::WIDTH; ++x){
				if(field_.getBlock(x, y) == Field::LADDER2)
					field_.setBlock(Field::LADDER, x, y);
				if(field_.getBlock(x, y) == Field::BRICK2)
					field_.setBlock(Field::BRICK, x, y);
			}
		}
	}

	if (!player_.tick(field_, enemies))
	{
		enemies.clear();
		player_.deleteTrap();
		field_ = Field();
		Enemy *enemy;
		for (unsigned int i = 0; i < field_.xvec.size(); i++){
			enemy = new Enemy(field_.xvec[i], field_.yvec[i]);
			enemies.push_back(*enemy);
			delete enemy;
		}
		player_ = Player(field_);
	}
}