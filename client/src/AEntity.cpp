/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** AEntity
*/

#include <SFML/Graphics/Sprite.hpp>

#include "AEntity.hpp"

rtype::AEntity::AEntity(const std::string &texture, sf::Vector2f position, sf::IntRect rectangle)
{
    _texture.loadFromFile(texture);

    _position._x = position.x;
    _position._y = position.y;

    _animation._height = rectangle.height;
    _animation._width = rectangle.width;
    _animation._x = rectangle.top;
    _animation._y = rectangle.left;
}

void rtype::AEntity::display(sf::RenderWindow &window)
{
    sf::Sprite sprite;

    sprite.setTexture(_texture);
    sprite.setPosition({ _position._x, _position._y });
    sprite.setTextureRect({ _animation._x, _animation._y, _animation._height, _animation._width });
    
    window.draw(sprite);
}
