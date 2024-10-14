/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Utils
*/

#include <cstdint>
#include <vector>

namespace ecs::utils {
    int bytesToInt(std::vector<uint8_t> &bytes)
    {
        return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
    }

    std::vector<uint8_t> intToBytes(int value)
    {
        std::vector<uint8_t> bytes(4);
        bytes[0] = (value >> 24) & 0xFF;
        bytes[1] = (value >> 16) & 0xFF;
        bytes[2] = (value >> 8) & 0xFF;
        bytes[3] = value & 0xFF;
        return bytes;
    }
} // namespace ecs::utils
