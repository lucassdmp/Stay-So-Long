#include <GL/gl.h>
#include "Game.hpp"
#include "../Util/Shapes.hpp"
#include "../Entities/Player.hpp"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 720

Game::Game()
{
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  this->window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Stay So Long");
  this->player = Player(100, 100, 5.0f, glm::vec2(100, 100), glm::vec2(30, 60), sf::Color::Red);

  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);
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

  this->player.draw(this->dt, *this->window);
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

  if (this->event.type == sf::Event::MouseButtonPressed)
  {
    if (this->event.mouseButton.button == sf::Mouse::Left)
      this->player.getGun().setShooting(true);
  }
  if (this->event.type == sf::Event::MouseButtonReleased)
  {
    if (this->event.mouseButton.button == sf::Mouse::Left)
      this->player.getGun().setShooting(false);
  }
}