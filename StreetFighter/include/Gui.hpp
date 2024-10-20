/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Gui
*/

#ifndef GUI_HPP_
#define GUI_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
#include "Game.hpp"

namespace street_fighter {
    /// @brief Gui Class is the class to handle the displayable at the screen, the game send him information and the Gui just display
    class Gui {
        public:
            /// @brief Gui constructor take a game to take any game as possible
            Gui(Game &game);

            /// @brief run function is the main loop with the display of every entity and running all the systems
            /// @return an int about the state if there is an error or not
            int run();

            /// @brief handleEvents function handle all events of the game with an while pool events of the SFML 
            /// @return an int about the state of the events, if there is error or not
            int handleEvents();

            /// @brief display function display all entities in the registry in the game that is "displayable"
            void display();

        private:
            Game _game;
            sf::RenderWindow _window;
    };
}

#endif /* !GUI_HPP_ */
