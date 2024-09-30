/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Gui
*/

#ifndef GUI_HPP_
#define GUI_HPP_

#include "Context.hpp"

namespace rtype {
    class Gui : ecs::Context {
      public:
        Gui();
        ~Gui();

        int run() override;

      protected:
      private:
        void setupPlayer();
        void setupBackground();
        void setupWeapon();
        void setupBasicEnnemies();
    };
} // namespace rtype

#endif /* !GUI_HPP_ */
