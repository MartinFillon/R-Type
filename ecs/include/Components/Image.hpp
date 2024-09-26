/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Image
*/

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

    #include <SFML/Graphics/Image.hpp>
    #include <string>

namespace ecs {
    namespace component {
        struct Image {
            sf::Image _image;
            std::string _pathToImage;
        };
    };
};

#endif /* !IMAGE_HPP_ */
