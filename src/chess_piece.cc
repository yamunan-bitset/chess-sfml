#include <iostream>
#include "chess_piece.hh"

extern void Position(ChessPiece*);                    // position.cc
extern std::string ToNote(sf::Vector2f, ChessPiece*); // notation.cc

ChessPiece::ChessPiece(sf::RenderWindow& windowRef, const std::string& file_name) : window(windowRef)
{
  if (!texture.loadFromFile(file_name)) exit(-1);
  this->sprite.setTexture(this->texture);
  this->moving = false;
  this->sprite.setScale(128 / this->sprite.getGlobalBounds().width,
			128 / this->sprite.getGlobalBounds().height);
  this->turn.turn_number = 1;
}

ChessPiece::ChessPiece(ChessPiece&& rval) : window(rval.window)
{
  this->texture = std::move(rval.texture);
  this->sprite.setTexture(this->texture);
  this->sprite.setScale(rval.sprite.getScale());
  this->moving = std::move(rval.moving);
  this->turn.turn_number = 1;
}

ChessPiece::ChessPiece(const ChessPiece& lval): window(lval.window)
{
  this->texture = lval.texture;
  this->sprite.setTexture(this->texture);
  this->sprite.setScale(lval.sprite.getScale());
  this->moving = lval.moving;
  this->turn.turn_number = 1;
}

ChessPiece::~ChessPiece()
{
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
      this->setPosition(mouse_pos.x - this->sprite.getGlobalBounds().width  / 2,
			mouse_pos.y - this->sprite.getGlobalBounds().height / 2);
      if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{ // Left Button Released
	  this->moving     = false;
	  moving_piece     = false;
	  Position(this);
	  this->old_pos = this->getPosition();
	  if (this->just_played)
	    {
	      this->play_sound = true;
	      this->turn.turn_number++;
	      std::cout << this->turn.turn << std::endl;
	      this->just_played = false;
	    }
	  else this->just_played = false;
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
	{ // Left Button Pressed
	  this->moving     = true;
	  moving_piece     = true;
	  this->pos_note = ToNote(this->old_pos, this) + ToNote(this->new_pos, this);
	  std::cout << this->pos_note << std::endl;
	  this->setPosition(this->new_pos);
	  this->just_played = true;
	}
      else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) &&
	       mouse_pos.x > this->getPosition().x &&
	       mouse_pos.y > this->getPosition().y &&
	       mouse_pos.x < this->getPosition().x + this->sprite.getGlobalBounds().width &&
	       mouse_pos.y < this->getPosition().y + this->sprite.getGlobalBounds().height &&
	       !moving_piece) this->delete_sprite = true; // Right Button Pressed, then delete figure
    }
}
