#include <Graphics.hpp>

#include "chess_piece.hh"

void Position(ChessPiece* sprite)
{
  sf::Vector2f p = sprite->getPosition()
    + sf::Vector2f(sprite->getsize_x() / 2, sprite->getsize_y() / 2);
  sf::Vector2f new_pos = sf::Vector2f(sprite->getsize_x() * int(p.x / sprite->getsize_x()),
				      sprite->getsize_y() * int(p.y / sprite->getsize_y()));
  sprite->setPosition(new_pos);
}

void Position(ChessPiece& sprite)
{
  sf::Vector2f p = sprite.getPosition()
    + sf::Vector2f(sprite.getsize_x() / 2, sprite.getsize_y() / 2);
  sf::Vector2f new_pos = sf::Vector2f(sprite.getsize_x() * int(p.x / sprite.getsize_x()),
				      sprite.getsize_y() * int(p.y / sprite.getsize_y()));
  sprite.setPosition(new_pos);
}
