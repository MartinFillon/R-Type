/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ImageResolver
*/

#pragma once

#include <string>
#include <unordered_map>

namespace ECS {

class ImageResolver {
  public:
    ImageResolver(const std::string &);

    ~ImageResolver();

    std::string getImage(const std::string &, bool = false);

  protected:
  private:
    std::string _basePath;
    std::unordered_map<std::string, std::string> _cache;
};

} // namespace ECS
