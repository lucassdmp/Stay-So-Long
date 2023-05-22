#pragma once

#include "Entity.hpp"
#include "SFML/Graphics.hpp"

class Enemy : public Entity
{
public:
  Enemy(glm::vec2 pos, glm::vec2 size, sf::Color color);
  virtual ~Enemy();

  void fixedUpdate(glm::vec2 playerPos);
  void draw();

private:
  float rotationAngle;
};