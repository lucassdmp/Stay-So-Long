#include "GameObject.hpp"
#include <glm/glm.hpp>

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, sf::Color color) : pos(pos), size(size), color(color) {}
GameObject::GameObject() {}

void GameObject::move(glm::vec2 mov)
{
    this->pos += mov;
}