/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Utils
*/

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <cstdint>
#include <vector>

namespace ecs::utils {
    int bytesToInt(std::vector<uint8_t> &bytes);

    std::vector<uint8_t> intToBytes(int value);
} // namespace ecs::utils

#endif /* !UTILS_HPP_ */
