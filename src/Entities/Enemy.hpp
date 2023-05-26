#pragma once

#include "Entity.hpp"
#include "SFML/Graphics.hpp"
#include "Projectile.hpp"
#include <vector>

class Enemy : public Entity
{
enum EnemyType
{
  FOLLOWER,
  CHARGER,
  SHOOTER
};

public:
  Enemy(glm::vec2 pos, glm::vec2 size, sf::Color color);
  virtual ~Enemy();

  void fixedUpdate();
  void draw();

  void handleEnemyTypes();
  void handleCharger();
  void handleShooter();

private:
  glm::vec2 lookDir;
  float rotationAngle;
  EnemyType type = EnemyType::FOLLOWER;

  // charger variables
  bool isCharging = false;
  float chargeTimer = 0.0f;
  float chargeDuration = 5.0f;

  float chargingTimer = 0.0f;
  float chargingDuration = 5.0f;

  glm::vec2 sprintDir;
  bool isSprinting = false;
  float sprintTimer = 0.0f;
  float sprintDuration = 10.0f;

  // shooter variables
  float shootCooldown = 0.0f;
  float shootCooldownDuration = 5.0f;

  float bulletSpeed = 10.0f;
  float bulletDamage = 10.0f;
  std::vector<Projectile> bullets;
};