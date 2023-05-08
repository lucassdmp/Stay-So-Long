#pragma once

#include <SFML/Graphics.hpp>
#include "../Entities/Player.hpp"

class Game
{
private:
  sf::RenderWindow *window;
  sf::Event event;
  sf::Clock clock;
  float dt;
  Player player;

public:
  Game();
  ~Game();

  void Run();
  void Update();
  void Render();
  void HandleInput();
};