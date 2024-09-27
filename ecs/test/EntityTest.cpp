/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** *
*/

#include <criterion/assert.h>
#include <criterion/criterion.h>

#define private public
#include "Entity.hpp"

Test(Entity, testEntityGetId)
{
    ecs::Entity entity(4);

    cr_assert_eq(4, entity.getId());
}

Test(Entity, testEntityEqualOperator)
{
    ecs::Entity firstEntity(4);
    ecs::Entity secondeEntity(4);

    cr_assert_eq(secondeEntity.getId(), firstEntity.getId());
}
