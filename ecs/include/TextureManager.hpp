/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TextureManager
*/

#ifndef TEXTUREMANAGER_HPP_
#define TEXTUREMANAGER_HPP_

#include <filesystem>
#include <memory>
#include <spdlog/spdlog.h>
#include <string>
#include <unordered_map>

namespace ecs {
    template <typename Texture>
    class TextureManager {
      public:
        template <typename Function>
        TextureManager(Function &&f, const std::string &path)
        {
            for (const auto &entry : std::filesystem::directory_iterator(path)) {
                if (entry.is_directory()) {
                    for (const auto &newEntry : std::filesystem::directory_iterator(entry.path())) {
                        std::string path(newEntry.path().generic_string().c_str());
                        _textures[path] = f(path);
                    }
                    continue;
                }
                std::string path(entry.path().generic_string().c_str());
                _textures[path] = f(path);
            }
        }

        std::shared_ptr<Texture> getTexture(const std::string &pathToImage)
        {
            if (_textures.find(pathToImage) == _textures.end()) {
                spdlog::warn("Texture not found on: ({})", pathToImage);
                return nullptr;
            } else {
                return _textures[pathToImage];
            }
        }

      private:
        std::unordered_map<std::string, std::shared_ptr<Texture>> _textures;
    };
} // namespace ecs

#endif /* !TEXTUREMANAGER_HPP_ */
