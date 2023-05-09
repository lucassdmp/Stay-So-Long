#pragma once

#include <glm/glm.hpp>
#include <map>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Input
{
  public:
    static std::map<sf::Keyboard::Key, bool> keys;
    static glm::vec2 mouse_pos;
    static std::map<sf::Mouse::Button, bool> mouse_buttons;

    static void set_key(sf::Keyboard::Key key, bool value);
    static void set_mouse_pos(glm::vec2 pos);
    static void set_mouse_button(sf::Mouse::Button button, bool value);

    static bool get_key(sf::Keyboard::Key key) { return keys[key]; };
    static glm::vec2 get_mouse_pos() { return mouse_pos; };
    static bool get_mouse_button(sf::Mouse::Button button) { return mouse_buttons[button]; };
};