#pragma once

#include <SFML/Graphics.hpp>
#include "../Entities/Player.hpp"

class Game
{
private:
  sf::RenderWindow *window;
  sf::Event *event;
  sf::Clock *clock;
  sf::Time *time;
  sf::Time *deltaTime;
  Player player;

public:
  Game();
  ~Game();

  void Run();
  void Update();
  void Render();
  void HandleInput();
};