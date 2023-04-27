#pragma once

#include "../Util/GameObject.hpp"
#include "../Util/Shapes.hpp"
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class Projectile : public GameObject{
public:
    Projectile(glm::vec2 direction, glm::vec2 pos, glm::vec2 size, sf::Color color);
    Projectile();
    void draw();
    void update();
    void setDirection(glm::vec2 direction);
    glm::vec2 getDirection();
private:
    glm::vec2 direction;
};