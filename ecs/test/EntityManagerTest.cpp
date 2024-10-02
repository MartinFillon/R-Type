/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EntityManager
*/


#include <criterion/assert.h>
#include <criterion/criterion.h>

#define private public
#include "EntityManager.hpp"
#include "Entity.hpp"

Test(EntityManager, TestEntityManagerContructor)
{
    ecs::EntityManager normalConstructor;
    ecs::EntityManager addIdConstructor(0);
    ecs::EntityManager addEntityConstructor(ecs::Entity(1));

    cr_assert_eq(normalConstructor.size(), 0);
    cr_assert_eq(addIdConstructor.size(), 1);
    cr_assert_eq(addEntityConstructor.size(), 1);
}

Test(EntityManager, TestAddEntity)
{
    ecs::EntityManager manager(0);

    manager.addEntity(ecs::Entity(1));
    cr_assert_eq(manager.size(), 2);
}

Test(EntityManager, TestOperator)
{
    ecs::EntityManager manager(0);

    manager.addEntity(ecs::Entity(1));
    manager.addEntity(ecs::Entity(2));
    ecs::Entity firstEntity(manager[0]);
    ecs::Entity secondEntity(manager[1]);

    cr_assert_eq(firstEntity.getId(), 0);
    cr_assert_eq(secondEntity.getId(), 1);
}

Test(EntityManager, TestErase)
{
    ecs::EntityManager manager(0);

    manager.addEntity(ecs::Entity(1));
    manager.addEntity(ecs::Entity(2));

    manager.erase(1);
    cr_assert_eq(manager.size(), 2);
}

Test(EntityManager, TestLastEntity)
{
    ecs::EntityManager manager(0);

    manager.addEntity(ecs::Entity(1));
    manager.addEntity(ecs::Entity(2));

    cr_assert_eq(manager.lastEntity(), 2);
}
