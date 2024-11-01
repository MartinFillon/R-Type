/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** KeyPressed
*/

#ifndef KEYPRESSED_HPP_
#define KEYPRESSED_HPP_

#include <string>
#include "IComponent.hpp"
#include <unordered_map>

namespace ecs {
    namespace component {
        enum Key {
            NoneKey,
            Jump,
            Up,
            Down,
            Right,
            Left,
            Punch,
            Kick,
            A,          //!< The A key
            B,          //!< The B key
            C,          //!< The C key
            D,          //!< The D key
            E,          //!< The E key
            F,          //!< The F key
            G,          //!< The G key
            H,          //!< The H key
            I,          //!< The I key
            J,          //!< The J key
            K,          //!< The K key
            L,          //!< The L key
            M,          //!< The M key
            N,          //!< The N key
            O,          //!< The O key
            P,          //!< The P key
            Q,          //!< The Q key
            R,          //!< The R key
            S,          //!< The S key
            T,          //!< The T key
            U,          //!< The U key
            V,          //!< The V key
            W,          //!< The W key
            X,          //!< The X key
            Y,          //!< The Y key
            Z,          //!< The Z key
            Num0,       //!< The 0 key
            Num1,       //!< The 1 key
            Num2,       //!< The 2 key
            Num3,       //!< The 3 key
            Num4,       //!< The 4 key
            Num5,       //!< The 5 key
            Num6,       //!< The 6 key
            Num7,       //!< The 7 key
            Num8,       //!< The 8 key
            Num9,       //!< The 9 key
            Escape,     //!< The Escape key
            LControl,   //!< The left Control key
            LShift,     //!< The left Shift key
            LAlt,       //!< The left Alt key
            LSystem,    //!< The left OS specific key: window (Windows and Linux), apple (macOS), ...
            RControl,   //!< The right Control key
            RShift,     //!< The right Shift key
            RAlt,       //!< The right Alt key
            RSystem,    //!< The right OS specific key: window (Windows and Linux), apple (macOS), ...
            Menu,       //!< The Menu key
            LBracket,   //!< The [ key
            RBracket,   //!< The ] key
            Semicolon,  //!< The ; key
            Comma,      //!< The , key
            Period,     //!< The . key
            Apostrophe, //!< The ' key
            Slash,      //!< The / key
            Backslash,  //!< The \ key
            Grave,      //!< The ` key
            Equal,      //!< The = key
            Hyphen,     //!< The - key (hyphen)
            Space,      //!< The Space key
            Enter,      //!< The Enter/Return keys
            Backspace,  //!< The Backspace key
            Tab,        //!< The Tabulation key
            PageUp,     //!< The Page up key
            PageDown,   //!< The Page down key
            End,        //!< The End key
            Home,       //!< The Home key
            Insert,     //!< The Insert key
            Delete,     //!< The Delete key
            Add,        //!< The + key
            Subtract,   //!< The - key (minus, usually from numpad)
            Multiply,   //!< The * key
            Divide,     //!< The / key
            Numpad0,    //!< The numpad 0 key
            Numpad1,    //!< The numpad 1 key
            Numpad2,    //!< The numpad 2 key
            Numpad3,    //!< The numpad 3 key
            Numpad4,    //!< The numpad 4 key
            Numpad5,    //!< The numpad 5 key
            Numpad6,    //!< The numpad 6 key
            Numpad7,    //!< The numpad 7 key
            Numpad8,    //!< The numpad 8 key
            Numpad9,    //!< The numpad 9 key
            F1,         //!< The F1 key
            F2,         //!< The F2 key
            F3,         //!< The F3 key
            F4,         //!< The F4 key
            F5,         //!< The F5 key
            F6,         //!< The F6 key
            F7,         //!< The F7 key
            F8,         //!< The F8 key
            F9,         //!< The F9 key
            F10,        //!< The F10 key
            F11,        //!< The F11 key
            F12,        //!< The F12 key
            F13,        //!< The F13 key
            F14,        //!< The F14 key
            F15,        //!< The F15 key
            Pause,      //!< The Pause key
            KeyCount,   //!< Keep last -- the total number of keyboard keys
            // Deprecated values:
            Tilde = Grave,         //!< \deprecated Use Grave instead
            Dash = Hyphen,         //!< \deprecated Use Hyphen instead
            BackSpace = Backspace, //!< \deprecated Use Backspace instead
            BackSlash = Backslash, //!< \deprecated Use Backslash instead
            SemiColon = Semicolon, //!< \deprecated Use Semicolon instead
            Return = Enter,        //!< \deprecated Use Enter instead
            Quote = Apostrophe     //!< \deprecated Use Apostrophe instead
        };

        struct KeyPressed : public IComponent {
            KeyPressed(Key key): _value(key) {}
            KeyPressed(): _value(NoneKey) {}
            Key _value;
            std::string _name = "Key Pressed";
            std::string getName() const {
                return _name;
            }
            std::string getInfo() const {
                std::unordered_map<Key, std::string> keyNames = {
                    {NoneKey, "NoneKey"}, {Jump, "Jump"}, {Up, "Up"}, {Down, "Down"},
                    {Right, "Right"}, {Left, "Left"}, {Punch, "Punch"}, {Kick, "Kick"},
                    {A, "A"}, {B, "B"}, {C, "C"}, {D, "D"}, {E, "E"}, {F, "F"}, {G, "G"},
                    {H, "H"}, {I, "I"}, {J, "J"}, {K, "K"}, {L, "L"}, {M, "M"}, {N, "N"},
                    {O, "O"}, {P, "P"}, {Q, "Q"}, {R, "R"}, {S, "S"}, {T, "T"}, {U, "U"},
                    {V, "V"}, {W, "W"}, {X, "X"}, {Y, "Y"}, {Z, "Z"},
                    {Num0, "Num0"}, {Num1, "Num1"}, {Num2, "Num2"}, {Num3, "Num3"},
                    {Num4, "Num4"}, {Num5, "Num5"}, {Num6, "Num6"}, {Num7, "Num7"},
                    {Num8, "Num8"}, {Num9, "Num9"}, {Escape, "Escape"}, {LControl, "LControl"},
                    {LShift, "LShift"}, {LAlt, "LAlt"}, {LSystem, "LSystem"}, {RControl, "RControl"},
                    {RShift, "RShift"}, {RAlt, "RAlt"}, {RSystem, "RSystem"}, {Menu, "Menu"},
                    {LBracket, "LBracket"}, {RBracket, "RBracket"}, {Semicolon, "Semicolon"},
                    {Comma, "Comma"}, {Period, "Period"}, {Apostrophe, "Apostrophe"},
                    {Slash, "Slash"}, {Backslash, "Backslash"}, {Grave, "Grave"},
                    {Equal, "Equal"}, {Hyphen, "Hyphen"}, {Space, "Space"}, {Enter, "Enter"},
                    {Backspace, "Backspace"}, {Tab, "Tab"}, {PageUp, "PageUp"},
                    {PageDown, "PageDown"}, {End, "End"}, {Home, "Home"}, {Insert, "Insert"},
                    {Delete, "Delete"}, {Add, "Add"}, {Subtract, "Subtract"},
                    {Multiply, "Multiply"}, {Divide, "Divide"}, {Numpad0, "Numpad0"},
                    {Numpad1, "Numpad1"}, {Numpad2, "Numpad2"}, {Numpad3, "Numpad3"},
                    {Numpad4, "Numpad4"}, {Numpad5, "Numpad5"}, {Numpad6, "Numpad6"},
                    {Numpad7, "Numpad7"}, {Numpad8, "Numpad8"}, {Numpad9, "Numpad9"},
                    {F1, "F1"}, {F2, "F2"}, {F3, "F3"}, {F4, "F4"}, {F5, "F5"}, {F6, "F6"},
                    {F7, "F7"}, {F8, "F8"}, {F9, "F9"}, {F10, "F10"}, {F11, "F11"}, {F12, "F12"},
                    {F13, "F13"}, {F14, "F14"}, {F15, "F15"}, {Pause, "Pause"}
                };

                return "Key: " + keyNames[_value];
            }
        };
    }; // namespace component
}; // namespace ecs

#endif /* !KEYPRESSED_HPP_ */
