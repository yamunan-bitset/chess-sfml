#include "chess_piece.hh"

ChessPiece::ChessPiece(sf::RenderWindow& windowRef, const std::string& file_name) : window(windowRef)
{
  if (!texture.loadFromFile(file_name)) exit(0);
  this->sprite.setTexture(this->texture);
  this->moving = false;
  this->sprite.setScale(128 / this->sprite.getGlobalBounds().width,
			128 / this->sprite.getGlobalBounds().height);
}

ChessPiece::ChessPiece(ChessPiece&& rval) : window(rval.window)
{
  this->texture = std::move(rval.texture);
  this->sprite.setTexture(this->texture);
  this->sprite.setScale(rval.sprite.getScale());
  this->moving = std::move(rval.moving);
}

ChessPiece::ChessPiece(const ChessPiece& lval): window(lval.window)
{
  this->texture = lval.texture;
  this->sprite.setTexture(this->texture);
  this->sprite.setScale(lval.sprite.getScale());
  this->moving = lval.moving;
}

void ChessPiece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= this->getTransform();
  target.draw(this->sprite,states);
}

void ChessPiece::move(bool& moving_piece)
{
  sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
  if (this->moving)
    {
      this->setPosition(mouse_pos.x - this->sprite.getGlobalBounds().width/2,
			mouse_pos.y - this->sprite.getGlobalBounds().height/2);
      if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
	  this->moving = false;
	  moving_piece = false;
	}
    }
  else
    {
      if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
	  mouse_pos.x > this->getPosition().x &&
	  mouse_pos.y > this->getPosition().y &&
	  mouse_pos.x < this->getPosition().x + this->sprite.getGlobalBounds().width &&
	  mouse_pos.y < this->getPosition().y + this->sprite.getGlobalBounds().height &&
	  !moving_piece)
	{
	  this->moving = true;
	  moving_piece = true;
	}
    }
}