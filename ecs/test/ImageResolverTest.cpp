/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ImageResolverTest
*/

#include "ImageResolver.hpp"

#include <criterion/assert.h>
#include <criterion/criterion.h>

Test(ImageResolver, test1)
{
    ECS::ImageResolver resolver("./");
    std::string file = resolver.getImage("README.md");
    cr_assert_strings_neq(file.c_str(), "");
}
