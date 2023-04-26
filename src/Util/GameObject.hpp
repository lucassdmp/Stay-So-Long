#pragma once

#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>


class GameObject{
    protected:
        glm::vec2 pos;
        glm::vec2 size;
        sf::Color color;
    public:
        GameObject();
        GameObject(glm::vec2 pos, glm::vec2 size, sf::Color color);
        glm::vec2 getPos();
        glm::vec2 getSize();
        sf::Color getColor();
        void setPos(glm::vec2 pos);
        void setSize(glm::vec2 size);
        void setColor(sf::Color color); 
        void move(glm::vec2 mov);
};