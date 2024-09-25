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
    ECS::ImageResolver resolver("./");
    std::string file = resolver.getImage("README.md");
    cr_assert_strings_neq(file.c_str(), "");
}

Test(ImageResolver, test2)
{
    ECS::ImageResolver resolver("./");
    std::string file = resolver.getImage("README.md");

    cr_assert_strings_eq(resolver._cache.at("README.md").c_str(), file.c_str());
}
