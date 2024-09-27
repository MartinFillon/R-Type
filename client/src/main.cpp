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
#include "Entity.hpp"
#include "Registry.hpp"
#include "Systems/PlayerMouvementSystem.hpp"
#include "Components/Drawable.hpp"

int main(void)
{
    ecs::Context ctx;
    return ctx.run();
}
