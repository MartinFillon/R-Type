/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RegistryTest
*/

#include <criterion/assert.h>
#include <criterion/criterion.h>

#include "Registry.hpp"
#define private public

Test(Registry, RegistrySpawnEntity)
{
    ecs::Registry r;

    cr_assert_eq(r.spawn_entity().getId(), 0);

    cr_assert_eq(r.spawn_entity().getId(), 1);
}

Test(Registry, RegisterComponent)
{
    ecs::Registry r;

    auto &positions = r.register_component<ecs::component::Position>();

    cr_assert_eq(positions.size(), 0);

    auto &positions2 = r.register_component<ecs::component::Position>();
    cr_assert_eq(&positions, &positions2);
}

Test(Registry, EraseEntity)
{
    ecs::Registry r;

    ecs::Entity e1 = r.spawn_entity();

    auto &positions = r.register_component<ecs::component::Position>();
    positions[0] = ecs::component::Position{10, 20};
    positions[1] = ecs::component::Position{30, 40};

    cr_assert_eq(positions[e1.getId()]->_x, 10);

    r.erase(0);

    cr_assert_eq(positions[1]->_x, 30);
}

Test(Registry, AddAndRunSystem)
{
    ecs::Registry r;

    ecs::Entity e1 = r.spawn_entity();
    ecs::Entity e2 = r.spawn_entity();

    auto &positions = r.register_component<ecs::component::Position>();
    positions[0] = ecs::component::Position{10, 20};
    positions[1] = ecs::component::Position{30, 40};

    r.add_system([](ecs::Registry &reg) {
        auto &positions = reg.get_components<ecs::component::Position>();
        for (std::size_t i = 0; i < positions.size(); ++i) {
            if (positions[i]) {
                positions[i]->_x += 10;
            }
        }
    });

    r.run_systems();

    cr_assert_eq(positions[e1.getId()]->_x, 20);
    cr_assert_eq(positions[e2.getId()]->_x, 40);
}
