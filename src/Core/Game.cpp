#include <GL/gl.h>
#include "Game.hpp"
#include "../Util/Shapes.hpp"
#include "../Entities/Player.hpp"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 720

Game::Game()
{
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  this->window = new sf::RenderWindow(sf::VideoMode(desktop.width, desktop.height), "Stay So Long", sf::Style::Fullscreen);
  this->player = Player(100, 100, 5.0f, glm::vec2(100, 100), glm::vec2(30, 70), sf::Color::Red);

  glViewport(0, 0, desktop.width, desktop.height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, desktop.width, 0, desktop.height, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  window->setFramerateLimit(60);
}

Game::~Game()
{
  delete this->window;
}

void Game::Run()
{
  while (this->window->isOpen())
  {
    while (this->window->pollEvent(this->event))
    {
      this->HandleInput();
    }
    this->dt = this->clock.restart().asSeconds();
    this->Render();
  }
}

void Game::Render()
{
  this->window->clear(sf::Color::Black);

  this->player.draw(this->dt);
  this->player.updateAttacks();

  this->window->display();
}

void Game::HandleInput()
{
  if (this->event.type == sf::Event::Closed)
    this->window->close();

  if (this->event.type == sf::Event::KeyPressed)
  {
    if (this->event.key.code == sf::Keyboard::Escape)
      this->window->close();

    if (this->event.key.code == sf::Keyboard::W)
      this->player.moveUp();

    if (this->event.key.code == sf::Keyboard::S)
      this->player.moveDown();

    if (this->event.key.code == sf::Keyboard::D)
      this->player.moveRight();

    if (this->event.key.code == sf::Keyboard::A)
      this->player.moveLeft();
    if (this->event.key.code == sf::Keyboard::Space)
      this->player.attack();
  }
  if (this->event.type == sf::Event::KeyReleased)
  {
    if (this->event.key.code == sf::Keyboard::W)
      this->player.stopUp();

    if (this->event.key.code == sf::Keyboard::S)
      this->player.stopDown();

    if (this->event.key.code == sf::Keyboard::D)
      this->player.stopRight();

    if (this->event.key.code == sf::Keyboard::A)
      this->player.stopLeft();
  }
}