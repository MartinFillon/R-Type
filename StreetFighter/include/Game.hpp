/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** StreetFighter Game Class
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <memory>
#include "ComponentFactory.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

#define SECOND_GAME_NAME "Epitech Fighter"

#define NORMAL_Y_POSITION 500

#define JUMP_ANIMATION_WIDTH 65
#define JUMP_ANIMATION_HEIGHT 80
#define JUMP_ANIMATION_X 0
#define JUMP_ANIMATION_Y 640

#define SIT_ANIMATION_X 0
#define SIT_ANIMATION_Y 740
#define SIT_ANIMATION_WIDTH 65
#define SIT_ANIMATION_HEIGHT 65
#define SIT_POSITION_Y 600

#define PUNCH_ANIMATION_X 0
#define PUNCH_ANIMATION_Y 160
#define PUNCH_ANIMATION_WIDTH 65
#define PUNCH_ANIMATION_HEIGHT 80

#define KICK_ANIMATION_X 0
#define KICK_ANIMATION_Y 480
#define KICK_ANIMATION_WIDTH 65
#define KICK_ANIMATION_HEIGHT 80

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

        std::shared_ptr<ecs::Registry> _r;

      private:
        ecs::ComponentFactory _factory;
    };
}; // namespace street_fighter

#endif /* !GAME_HPP_ */
