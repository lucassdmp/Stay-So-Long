#pragma once

#include "../Util/GameObject.hpp"
#include "../Util/Shapes.hpp"
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class Projectile : public GameObject{
public:
    Projectile();
    Projectile(glm::vec2 direction, float speed, glm::vec2 pos, glm::vec2 size, sf::Color color);
    virtual ~Projectile();
    void draw();
    void update();
    void setDirection(glm::vec2 direction);
    glm::vec2 getDirection();
private:
    glm::vec2 direction;
    float speed;
};