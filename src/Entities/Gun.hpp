#pragma once

#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Projectile.hpp"
#include <vector>
#include <iostream>

class Gun
{
  private:
    glm::vec2 pos;
    glm::vec2 offset = glm::vec2(20.0f, 0.0f);
    std::vector<Projectile> projectiles;
    float angle = 0.0f;
    float shot_cooldown = 2.0f;
    float shot_timer = 0.0f;

  public:
    Gun();
    ~Gun();

    void shoot();
    void update(glm::vec2 player_pos, sf::RenderWindow &window, Entity &player);
    void handleShots(sf::RenderWindow &window);
    void draw();
};