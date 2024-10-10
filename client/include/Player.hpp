/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

#include "AEntity.hpp"

namespace rtype {

    class Player: AEntity {

        public:

            Player(sf::Vector2f position, uint8_t type): AEntity(textures[type], position, rectangles[type]) {};

            void update() {};

    };

}; // namespace rtype

#endif /* !PLAYER_HPP_ */
