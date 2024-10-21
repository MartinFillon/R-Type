/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** StreetFighter Game Class
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "Entity.hpp"

#define SECOND_GAME_NAME "Epitech Fighter"

#define JUMP_ANIMATION_WIDTH 100
#define JUMP_ANIMATION_HEIGHT 135
#define JUMP_ANIMATION_X 0
#define JUMP_ANIMATION_Y 650

#define SIT_ANIMATION_X 0
#define SIT_ANIMATION_Y 528

#include "ComponentFactory.hpp"
#include "Registry.hpp"

/// @brief street_fighter namespace for all calsses that concern the Street Fighter Game
namespace street_fighter {
    class Game {
        public:
            /// @brief Game constructor that setup all entities of the street fighter with the component
            /// factory and add it to his registry
            Game();
            ~Game() = default;

            /// @brief run functions is running all systems and send it to the gui that run the game
            /// @return an int for the error or good value
            int run();

            /// @brief findPlayerIndex functions find the current player index
            /// @return it as an Entity 
            ecs::Entity findPlayerIndex();

            ecs::Registry _r;
        private:
            ecs::ComponentFactory _factory;
    };
};

#endif /* !GAME_HPP_ */
