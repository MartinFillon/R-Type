/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TextureManager
*/

#ifndef TEXTUREMANAGER_HPP_
#define TEXTUREMANAGER_HPP_

#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <string>
#include <unordered_map>

#define PATH_TO_ASSETS "assets/sprites/"

namespace rtype {
    class TextureManager {
      public:
        TextureManager();

        sf::Texture &getTexture(const std::string &pathToImage);

      private:
        std::unordered_map<std::string, std::unique_ptr<sf::Texture>> _textures;
    };
} // namespace rtype

#endif /* !TEXTUREMANAGER_HPP_ */
