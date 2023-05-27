#pragma once

#include <SFML/Graphics.hpp>
#include "../Entities/Player.hpp"
#include "../Entities/Asteroid.hpp"
#include "World.hpp"
#include <map>

class Game
{
private:
  sf::Event event;
  sf::Clock clock;
  sf::Texture *background_texture;
  sf::Sprite background;
  sf::Font *font;

public:
  Game();
  ~Game();

  void Run();
  void Update();
  void Render();
  void HandleInput();

  static void Pause();
  static void Resume();

  static bool isPaused;
  static sf::RenderWindow *window;
  static World *world;
  static float dt;
  static std::map<std::string, sf::Text> texts;
};