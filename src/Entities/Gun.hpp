#pragma once

#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>

class Gun
{
  private:
    glm::vec2 pos;
    float angle = 0.0f;

  public:
    Gun();
    Gun(glm::vec2 initial_pos);
    ~Gun();

    void shoot();
    void update(glm::vec2 player_pos, sf::RenderWindow &window);
    void draw();
};