/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GravitableMouvementSystem
*/

#include "Systems/GravitableMouvementSystem.hpp"
#include "Components/Animations.hpp"
#include "Components/Gravitable.hpp"
#include "Components/Position.hpp"
#include "ZipperIterator.hpp"

void ecs::systems::GravitableMouvementSystem::operator()(Registry &r, std::shared_ptr<IContext> ctx)
{
    auto &positions = r.get_components<ecs::component::Position>();
    auto &animations = r.get_components<ecs::component::Animations>();
    auto &gravitables = r.get_components<ecs::component::Gravitable>();

    for (auto &&[pos] : custom_zip(positions)) {
        if (!pos) {
            continue;
        }


    }
}
