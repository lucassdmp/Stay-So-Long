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
  float rotationAngle = 0.0f;

public:
  Asteroid(glm::vec2 playerPos, glm::vec2 size);
  virtual ~Asteroid();

  void move();
  void draw();

  void setDirection(glm::vec2 value) { this->direction = value; }
  void setOutOfBoundsTimer(float value) { this->outOfBoundsTimer = value; }

  void setDirectionAndInitialPosition(glm::vec2 playerPos);

  void generateVertices();
  std::vector<glm::vec2> getVertices() { return vertices; }

  glm::vec2 getDirection() { return direction; }
  float getOutOfBoundsTimer() { return outOfBoundsTimer; }
};