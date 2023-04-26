#pragma once

#include <SFML/Graphics.hpp>

class Game
{
private:
  sf::RenderWindow* window;
  sf::Event* event;
  sf::Clock* clock;
  sf::Time* time;
  sf::Time* deltaTime;

public:
  Game();
  ~Game();

  void Run();
  void Update();
  void Render();
  void HandleInput();
};