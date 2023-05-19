#pragma once

#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>

class GameObject
{
protected:
    glm::vec2 pos;
    glm::vec2 size;
    sf::Color color;

public:
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, sf::Color color);
    glm::vec2 getPos() { return this->pos; }
    glm::vec2 getSize() { return this->size; }
    sf::Color getColor() { return this->color; }
    void setPos(glm::vec2 pos) { this->pos = pos; }
    void setSize(glm::vec2 size) { this->size = size; }
    void setColor(sf::Color color) { this->color = color; }
    void move(glm::vec2 mov);
};