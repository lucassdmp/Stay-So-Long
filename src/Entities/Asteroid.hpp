#pragma once

#include "Entity.hpp"
#include <iostream>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <random>

class Asteroid : public Entity
{
private:
  std::vector<glm::vec2> vertices;
  glm::vec2 direction;
  float outOfBoundsTimer = 0.0f;

public:
  Asteroid(glm::vec2 playerPos, glm::vec2 size);
  virtual ~Asteroid();

  void move();
  void draw();

  void setDirectionAndInitialPosition(glm::vec2 playerPos);

  void generateVertices();
  std::vector<glm::vec2> getVertices() { return vertices; }

  float getOutOfBoundsTimer() { return outOfBoundsTimer; }
};