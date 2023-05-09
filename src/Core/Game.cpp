#include <GL/gl.h>
#include "Game.hpp"
#include "../Util/Shapes.hpp"
#include "../Entities/Player.hpp"
#include "../Util/Input.hpp"
#include <iostream>

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

  this->player.fixedUpdate(this->dt, *this->window);

  this->window->display();
}

void Game::HandleInput()
{
  if (this->event.type == sf::Event::Closed)
    this->window->close();

  // handle keyboard input
  if (this->event.type == sf::Event::KeyPressed)
  {
    Input::set_key(this->event.key.code, true);
    if (this->event.key.code == sf::Keyboard::Escape)
      this->window->close();
  }
  if (this->event.type == sf::Event::KeyReleased)
    Input::set_key(this->event.key.code, false);

  // handle mouse input
  if (this->event.type == sf::Event::MouseButtonPressed)
    Input::set_mouse_button(this->event.mouseButton.button, true);
  if (this->event.type == sf::Event::MouseButtonReleased)
    Input::set_mouse_button(this->event.mouseButton.button, false);

  // handle mouse movement
  if (this->event.type == sf::Event::MouseMoved)
    Input::set_mouse_pos(glm::vec2(this->event.mouseMove.x, this->event.mouseMove.y));
}