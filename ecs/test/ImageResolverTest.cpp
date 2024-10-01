/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ImageResolverTest
*/

#include <criterion/assert.h>
#include <criterion/criterion.h>

#define private public
#include "ImageResolver.hpp"

Test(ImageResolver, test1)
{
    ecs::ImageResolver resolver("./");
    std::string file = resolver.getImage("README.md");

    cr_assert_eq(file.size(), 0);
}
