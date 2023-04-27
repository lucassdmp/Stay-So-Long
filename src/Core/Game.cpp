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
  this->event = new sf::Event();
  this->clock = new sf::Clock();
  this->time = new sf::Time();
  this->deltaTime = new sf::Time();
  this->player = Player(100, 100, 3, glm::vec2(100, 100), glm::vec2(10, 20), sf::Color::Red);

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
  delete this->event;
  delete this->clock;
  delete this->time;
  delete this->deltaTime;
}

void Game::Run()
{
  while (this->window->isOpen())
  {
    while (this->window->pollEvent(*this->event))
    {
      this->HandleInput();
    }
    *this->deltaTime = this->clock->restart();
    this->Render();
  }
}

void Game::Render()
{
  this->window->clear(sf::Color::Black);

  glPushMatrix();

  glTranslatef(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
  Shapes::Circle(1, 36);
  glPopMatrix();

  this->player.draw();
  this->player.updateAttacks();

  this->window->display();
}

void Game::HandleInput()
{
  if (this->event->type == sf::Event::Closed)
    this->window->close();

  if (this->event->type == sf::Event::KeyPressed)
  {
    if (this->event->key.code == sf::Keyboard::Escape)
      this->window->close();

    if (this->event->key.code == sf::Keyboard::W)
      this->player.moveUp();

    if (this->event->key.code == sf::Keyboard::S)
      this->player.moveDown();

    if (this->event->key.code == sf::Keyboard::D)
      this->player.moveRight();

    if (this->event->key.code == sf::Keyboard::A)
      this->player.moveLeft();
    if (this->event->key.code == sf::Keyboard::Space)
      this->player.attack();
  }
  if (this->event->type == sf::Event::KeyReleased)
  {
    if (this->event->key.code == sf::Keyboard::W)
      this->player.stopUp();

    if (this->event->key.code == sf::Keyboard::S)
      this->player.stopDown();

    if (this->event->key.code == sf::Keyboard::D)
      this->player.stopRight();

    if (this->event->key.code == sf::Keyboard::A)
      this->player.stopLeft();
  }
}