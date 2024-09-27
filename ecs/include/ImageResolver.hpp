/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ImageResolver
*/

#ifndef IMAGERESOLVER_HPP_
#define IMAGERESOLVER_HPP_

#include <string>
#include <unordered_map>

#define PATH_TO_ASSETS "assets/sprites/"

namespace ecs {

    /**
     * An image loader that caches images
     */
    class ImageResolver {
      public:
        ImageResolver(const std::string &);

        ~ImageResolver();

        /**
         * @brief Get the Image content
         * @param path The path to the image
         * @param reload If the image should be reloaded (default: false)
         *
         * @return The image content
         */
        std::string getImage(const std::string &, bool = false);

      protected:
      private:
        std::string _basePath;
        std::unordered_map<std::string, std::string> _cache;
    };

} // namespace ecs

#endif // IMAGERESOLVER_HPP_
