/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** AEntity
*/

#ifndef AENTITY_HPP_
    #define AENTITY_HPP_

#include <SFML/Graphics/Texture.hpp>

#include "IEntity.hpp"
#include "Components/Position.hpp"
#include "Components/Animations.hpp"

namespace rtype {

    class AEntity: IEntity {

        public:

            AEntity(const std::string &texture, sf::Vector2f position, sf::IntRect rectangle);

            void display(sf::RenderWindow &window);

        private:

            sf::Texture _texture;

        protected:

            ecs::component::Position _position;
            ecs::component::Animations _animation;

    };

}; // namespace rtype

#endif /* !AENTITY_HPP_ */
