#pragma once

#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Gun
{
  private:
    glm::vec2 pos;
    float angle = 0.0f;
    glm::vec2 offset = glm::vec2(20.0f, 0.0f);

  public:
    Gun();
    ~Gun();

    void shoot();
    void update(glm::vec2 player_pos, sf::RenderWindow &window, Entity &player);
    void draw();
};