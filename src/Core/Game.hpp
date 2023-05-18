#pragma once

#include <SFML/Graphics.hpp>
#include "../Entities/Player.hpp"
#include "../Entities/Asteroid.hpp"
#include "World.hpp"

class Game
{
private:
  sf::Event event;
  sf::Clock clock;
  sf::Texture *background_texture;
  sf::Sprite background;
  float dt;

public:
  Game();
  ~Game();

  void Run();
  void Update();
  void Render();
  void HandleInput();

  static sf::RenderWindow *window;
  static World *world;
};