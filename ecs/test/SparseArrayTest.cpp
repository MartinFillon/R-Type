/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SparseArrayTest
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "SparseArray.hpp"

Test(SparseArray, InsertionAndAccess)
{
    ecs::SparseArray<int> array;

    array[0] = 5;
    array[2] = 10;

    cr_assert_eq(array[0].value(), 5);
    cr_assert_eq(array[2].value(), 10);

    cr_assert(!array[1].has_value());
}

Test(SparseArray, ResizeOnAccess)
{
    ecs::SparseArray<int> array;

    cr_assert_eq(array.size(), 0);
    array[5] = 100;
    cr_assert_eq(array.size(), 6);
    cr_assert_eq(array[5].value(), 100);
}

Test(SparseArray, Erase)
{
    ecs::SparseArray<int> array;

    array[0] = 5;
    array[1] = 10;

    array.erase(0);

    cr_assert(!array[0].has_value());
    cr_assert_eq(array[1].value(), 10);
}

Test(SparseArray, CopyConstructor)
{
    ecs::SparseArray<int> array;

    array[0] = 5;
    array[2] = 10;

    ecs::SparseArray<int> copy(array);

    cr_assert_eq(copy[0].value(), 5);
    cr_assert_eq(copy[2].value(), 10);
}

Test(SparseArray, MoveConstructor)
{
    ecs::SparseArray<int> array;

    array[0] = 5;
    array[2] = 10;

    ecs::SparseArray<int> moved(std::move(array));

    cr_assert_eq(moved[0].value(), 5);
    cr_assert_eq(moved[2].value(), 10);

    cr_assert_eq(array.size(), 0);
}

Test(SparseArray, IteratorUsage)
{
    ecs::SparseArray<int> array;

    array[0] = 5;
    array[1] = 10;
    array[3] = 15;

    int sum = 0;
    for (const auto &opt : array) {
        if (opt.has_value()) {
            sum += opt.value();
        }
    }

    cr_assert_eq(sum, 30);
}
