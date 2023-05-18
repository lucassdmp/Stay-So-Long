#pragma once

#include <SFML/Graphics.hpp>
#include "../Entities/Player.hpp"
#include "../Entities/Asteroid.hpp"
#include <iostream>
#include <vector>

class World
{
private:
  float *dt;
  sf::RenderWindow *window;
  Player *player;
  std::vector<Asteroid> asteroids;
  float asteroidTimer;
  float asteroidTimerMax;

public:
  World(float &dt, sf::RenderWindow &window);
  virtual ~World();

  void Update();
  void Render();

  void handleAsteroids();
};