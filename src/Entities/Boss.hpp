#pragma once

#include "Entity.hpp"
#include "Projectile.hpp"
#include <vector>

class Boss : public Entity
{
private:
  float shootTimer;
  float shootTimerMax;
  float rotation = 0.0f;
  std::vector<Projectile> projectiles;

public:
  Boss(glm::vec2 pos, glm::vec2 size, sf::Color color);
  virtual ~Boss();

  void update();
  void draw();
  void drawHealthBar();

  void shoot();

  std::vector<Projectile> &getProjectiles() { return projectiles; }
};