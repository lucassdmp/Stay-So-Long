#pragma once

#include <SFML/Graphics.hpp>
#include "../Entities/Player.hpp"
#include "../Entities/Asteroid.hpp"
#include "../Entities/Enemy.hpp"
#include <iostream>
#include <vector>

class World
{
private:
  float *dt;
  sf::RenderWindow *window;
  float asteroidTimer;
  float asteroidTimerMax;
  float enemyTimer;
  float enemyTimerMax;

public:
  World(float &dt, sf::RenderWindow &window);
  virtual ~World();

  void Update();
  void Render();

  void handleAsteroids();
  void handleEnemies();
  
  static Player *player;
  static std::vector<Asteroid> asteroids;
  static std::vector<Enemy> enemies;
};