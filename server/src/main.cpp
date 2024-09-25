/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main
*/

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "Context.hpp"

int main(void)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "ecs SFML Example");

    ecs::Context ctx = ecs::Context(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        window.display();
    }
    return 0;
}
