/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TextureManager
*/

#include <SFML/Graphics/Texture.hpp>
#include <filesystem>
#include <iostream>
#include <memory>

#include "TextureManager.hpp"

namespace rtype::client {
    TextureManager::TextureManager()
    {
        for (const auto &entry : std::filesystem::directory_iterator(PATH_TO_ASSETS)) {
            if (entry.is_directory()) {
                for (const auto &newEntry : std::filesystem::directory_iterator(entry.path())) {
                    std::string path(newEntry.path().generic_string().c_str());
                    std::string asstesPath = path.substr(15, path.size());
                    sf::Texture temp;

                    temp.loadFromFile(path);
                    _textures[asstesPath] = std::make_shared<sf::Texture>(temp);
                }
                continue;
            }
            std::string path(entry.path().generic_string().c_str());
            std::string asstesPath = path.substr(15, path.size());
            sf::Texture temp;

            temp.loadFromFile(path);
            _textures[asstesPath] = std::make_shared<sf::Texture>(temp);
        }
    }

    sf::Texture TextureManager::getTexture(const std::string &pathToImage)
    {
        if (_textures.find(pathToImage) == _textures.end()) {
            std::cerr << "Texture not found" << pathToImage << std::endl;
            return sf::Texture();
        } else {
            return *_textures[pathToImage].get();
        }
    }
} // namespace rtype::client
