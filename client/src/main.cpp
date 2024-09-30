/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main
*/

#include <memory>
#include "ComponentFactory.hpp"
#include "Context.hpp"
#include "Registry.hpp"

int main(void)
{
    // ecs::Context ctx;
    // return ctx.run();

    std::shared_ptr<ecs::Registry> r = std::make_shared<ecs::Registry>();
    ecs::ComponentFactory cf(r);

    cf.createEntity("config/background.json");
    return 0;
}
