#include "game.hpp"
#include "painter.hpp"
#include "field.hpp"
#include "player.hpp"

Game::Game():field_(), player_(field_){
}

void Game::tick()
{
  if (!player_.tick(field_))
  {
    field_ = Field();
    player_ = Player(field_);
  }
}

void Game::draw(Painter &p) const
{
  field_.draw(p);
}

void Game::keyEvent(Player::Direction d)
{
  player_.keyEvent(d);
}
