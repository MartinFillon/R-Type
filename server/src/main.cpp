/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main
*/

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "ImageResolver.hpp"

int main(void)
{
    // sf::RenderWindow window(sf::VideoMode(800, 600), "ECS SFML Example");

    // ECS::Context ctx = ECS::Context(window);

    // while (window.isOpen()) {
    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }
    //     window.clear();

    //     window.display();
    // }

    ECS::ImageResolver resolver("./");

    std::cout << resolver.getImage("README.md") << std::endl;
    std::cout << resolver.getImage("README.md") << std::endl;
    return 0;
}
