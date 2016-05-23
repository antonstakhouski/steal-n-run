#include "game.hpp"
#include "painter.hpp"
#include "field.hpp"
#include "player.hpp"

Game::Game():field_(), player_(field_){
}

void Game::draw(Painter &p) const
{
	field_.draw(p);
}

void Game::keyEvent(Player::Action d)
{
	player_.keyEvent(d);
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

	if (!player_.tick(field_))
	{
		field_ = Field();
		player_ = Player(field_);
	}
}
