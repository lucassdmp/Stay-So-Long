#include "Input.hpp"

void Input::set_key(sf::Keyboard::Key key, bool value)
{
  keys[key] = value;
}

void Input::set_mouse_pos(glm::vec2 pos)
{
  mouse_pos = pos;
}

void Input::set_mouse_button(sf::Mouse::Button button, bool value)
{
  mouse_buttons[button] = value;
}

std::map<sf::Keyboard::Key, bool> Input::keys;

glm::vec2 Input::mouse_pos;

std::map<sf::Mouse::Button, bool> Input::mouse_buttons;