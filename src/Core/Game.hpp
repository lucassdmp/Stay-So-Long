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
  sf::Texture *background_texture;
  sf::Sprite background;

public:
  Game();
  ~Game();

  void Run();
  void Update();
  void Render();
  void HandleInput();
};