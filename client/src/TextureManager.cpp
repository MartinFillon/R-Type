/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TextureManager
*/

#include <SFML/Graphics/Texture.hpp>
#include <filesystem>

#include "TextureManager.hpp"

namespace rtype {

    TextureManager::TextureManager()
    {
        for (const auto &entry : std::filesystem::directory_iterator(PATH_TO_ASSETS)) {
            if (entry.is_directory()) {
                for (const auto &newEntry : std::filesystem::directory_iterator(entry.path())) {
                    std::string path(newEntry.path().c_str());
                    std::string asstesPath = path.substr(15, path.size());
                    sf::Texture temp;

                    temp.loadFromFile(newEntry.path());
                    _textures[asstesPath] = std::make_unique<sf::Texture>(temp);
                }
                continue;
            }
            std::string path(entry.path().c_str());
            std::string asstesPath = path.substr(15, path.size());
            sf::Texture temp;

            temp.loadFromFile(entry.path());
            _textures[asstesPath] = std::make_unique<sf::Texture>(temp);
        }
    }

    sf::Texture &TextureManager::getTexture(const std::string &pathToImage)
    {
        return *_textures[pathToImage];
    }

} // namespace rtype
