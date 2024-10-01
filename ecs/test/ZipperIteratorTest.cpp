/*
** EPITECH PROJECT, 2024
** Zipper iterator test
** File description:
** r type proj
*/

#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <tuple>
#include <vector>
#include <algorithm>

#define private public
#include "ZipperIterator.hpp"

Test(custom_zip, iterates_over_single_array)
{
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    int expected = 1;
    ecs::custom_zip zip(vec1);
    auto it = zip.begin();
    auto end = zip.end();

    for (; it != end; ++it) {
        auto val = std::get<0>(*it);
        cr_assert_eq(val, expected++, "Expected %d, but got %d", expected-1, val);
    }

    cr_assert_eq(expected, 6);
}

Test(custom_zip, iterates_over_multiple_arrays)
{
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::vector<char> vec2 = {'a', 'b', 'c', 'd', 'e'};
    int expected_int = 1;
    char expected_char = 'a';

    ecs::custom_zip zip(vec1, vec2);
    auto it = zip.begin();
    auto end = zip.end();

    for (; it != end; ++it) {
        auto val1 = std::get<0>(*it);
        auto val2 = std::get<1>(*it);

        cr_assert_eq(val1, expected_int++, "Expected %d, but got %d", expected_int-1, val1);
        cr_assert_eq(val2, expected_char++, "Expected %c, but got %c", expected_char-1, val2);
    }

    cr_assert_eq(expected_int, 6);
    cr_assert_eq(expected_char, 'f');
}

Test(custom_zip, stops_at_minimum_size)
{
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::vector<char> vec2 = {'a', 'b', 'c'};

    ecs::custom_zip zip(vec1, vec2);

    auto it = zip.begin();
    auto end = zip.end();

    int expected_int = 1;
    char expected_char = 'a';
    int count = 0;
    for (; it != end; ++it) {
        auto val1 = std::get<0>(*it);
        auto val2 = std::get<1>(*it);

        cr_assert_eq(val1, expected_int++, "Expected %d, but got %d", expected_int-1, val1);
        cr_assert_eq(val2, expected_char++, "Expected %c, but got %c", expected_char-1, val2);
        count++;
    }

    cr_assert_eq(count, 3);
}

Test(custom_zip, empty_arrays)
{
    std::vector<int> vec1 = {};
    std::vector<char> vec2 = {};

    ecs::custom_zip zip(vec1, vec2);

    auto it = zip.begin();
    auto end = zip.end();

    cr_assert(it == end);
}
