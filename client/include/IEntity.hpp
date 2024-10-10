/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** IEntity
*/

#ifndef IENTITY_HPP_
    #define IENTITY_HPP_

    #include <map>
    #include <SFML/Graphics/RenderWindow.hpp>

    #define PLAYER_LEFT 65
    #define PLAYER_WIDTH 33
    #define PLAYER_HEIGHT 20
    #define PLAYER_TEXTURE "r-typesheet42.gif"

namespace rtype {

    class IEntity {

        public:

            virtual ~IEntity() = default;

            virtual void update() = 0;
            virtual void display(sf::RenderWindow &window) = 0;

    };

    static std::map<uint8_t, std::string> textures = {
        { 1, PLAYER_TEXTURE },
        { 2, PLAYER_TEXTURE },
        { 3, PLAYER_TEXTURE },
        { 4, PLAYER_TEXTURE }
    };

    static std::map<uint8_t, sf::IntRect> rectangles = {
        { 1, sf::IntRect(PLAYER_LEFT, 0 * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT) },
        { 2, sf::IntRect(PLAYER_LEFT, 1 * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT) },
        { 3, sf::IntRect(PLAYER_LEFT, 2 * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT) },
        { 4, sf::IntRect(PLAYER_LEFT, 3 * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT) }
    };

}; // namespace rtype

#endif /* !IENTITY_HPP_ */
