/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ImageResolver
*/

#include <fstream>
#include <stdexcept>

#include "ImageResolver.hpp"

namespace ecs {

    ImageResolver::ImageResolver(const std::string &path) : _basePath(path) {}

    ImageResolver::~ImageResolver() {}

    std::string readFile(const std::string &path)
    {
        std::ifstream file;
        std::string s;

        file.open(path);

        if (file.is_open()) {
            std::string line;
            while (getline(file, line)) {
                s += line;
                s += "\n";
            }
            file.close();
        }
        return s;
    }

    std::string ImageResolver::getImage(const std::string &path, bool reload)
    {
        if (reload) {
            _cache[path] = readFile(_basePath + path);
            return _cache.at(path);
        }
        try {
            return _cache.at(path);
        } catch (const std::out_of_range &e) {
            std::string s = readFile(_basePath + path);
            if (!s.empty())
                _cache[path] = s;
            return s;
        }
    }

} // namespace ecs
