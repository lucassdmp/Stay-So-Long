#pragma once

#include "Entity.hpp"
#include "SFML/Graphics.hpp"

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

  void fixedUpdate(glm::vec2 playerPos);
  void draw();

  void handleEnemyTypes(glm::vec2 playerPos);
  void handleCharger();

private:
  glm::vec2 lookDir;
  float rotationAngle;
  EnemyType type = EnemyType::FOLLOWER;

  // charger variables
  bool isCharging = false;
  float chargeTimer = 0.0f;
  float chargeDuration = 10.0f;

  float chargingTimer = 0.0f;
  float chargingDuration = 5.0f;

  glm::vec2 sprintDir;
  bool isSprinting = false;
  float sprintTimer = 0.0f;
  float sprintDuration = 5.0f;


};