/*
** EPITECH PROJECT, 2024
** Zipper iterator test
** File description:
** r type proj
*/

#include <algorithm>
#include <tuple>
#include <vector>
#include <criterion/assert.h>
#include <criterion/criterion.h>

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
        cr_assert_eq(val, expected++, "Expected %d, but got %d", expected - 1, val);
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

        cr_assert_eq(val1, expected_int++, "Expected %d, but got %d", expected_int - 1, val1);
        cr_assert_eq(val2, expected_char++, "Expected %c, but got %c", expected_char - 1, val2);
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

        cr_assert_eq(val1, expected_int++, "Expected %d, but got %d", expected_int - 1, val1);
        cr_assert_eq(val2, expected_char++, "Expected %c, but got %c", expected_char - 1, val2);
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

Test(custom_zip, different_types_in_tuples)
{
    std::vector<int> vec1 = {1, 2, 3};
    std::vector<double> vec2 = {1.1, 2.2, 3.3};
    std::vector<std::string> vec3 = {"one", "two", "three"};

    std::vector<int> expected_int = {1, 2, 3};
    std::vector<double> expected_double = {1.1, 2.2, 3.3};
    std::vector<std::string> expected_str = {"one", "two", "three"};

    size_t index = 0;

    for (auto &&[val1, val2, val3] : ecs::custom_zip(vec1, vec2, vec3)) {
        cr_assert_eq(val1, expected_int[index], "Incorrect int value at index %zu", index);
        cr_assert_float_eq(val2, expected_double[index], 1e-6, "Incorrect double value at index %zu", index);
        cr_assert_str_eq(val3.c_str(), expected_str[index].c_str(), "Incorrect string value at index %zu", index);


        index++;
    }

    cr_assert_eq(index, 3, "The loop should run 3 times, but ran %zu times", index);
}

Test(custom_zip, missing_element_in_one_array)
{
    std::vector<int> vec1 = {1, 2, 3};
    std::vector<double> vec2 = {1.1, 2.2};
    std::vector<std::string> vec3 = {"one", "two", "three"};

    std::vector<int> expected_int = {1, 2};
    std::vector<double> expected_double = {1.1, 2.2};
    std::vector<std::string> expected_str = {"one", "two"};

    size_t index = 0;

    for (auto &&[val1, val2, val3] : ecs::custom_zip(vec1, vec2, vec3)) {
        cr_assert_eq(val1, expected_int[index], "Incorrect int value at index %zu", index);
        cr_assert_float_eq(val2, expected_double[index], 1e-6, "Incorrect double value at index %zu", index);
        cr_assert_str_eq(val3.c_str(), expected_str[index].c_str(), "Incorrect string value at index %zu", index);


        index++;
    }

    cr_assert_eq(index, 2, "The loop should run 2 times, but ran %zu times", index);
}
