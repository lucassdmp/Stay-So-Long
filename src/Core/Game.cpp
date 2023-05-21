#include <GL/gl.h>
#include "Game.hpp"
#include "../Util/Shapes.hpp"
#include "../Entities/Player.hpp"
#include "../Util/Input.hpp"
#include <iostream>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

Game::Game()
{
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  this->window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Stay So Long");
  this->window->setPosition(sf::Vector2i((desktop.width / 2) - (SCREEN_WIDTH / 2), (desktop.height / 2) - (SCREEN_HEIGHT / 2)));
  this->window->setMouseCursorVisible(false);

  this->world = new World(this->dt, *this->window);

  glViewport(0, 0, window->getSize().x, window->getSize().y);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, window->getSize().x, window->getSize().y, 0, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  window->setFramerateLimit(60);

  background_texture = new sf::Texture();
  if (!background_texture->loadFromFile("../src/Assets/Backgrounds/Purple_01.png"))
    std::cout << "Error loading background texture" << std::endl;

  this->background.setTexture(*background_texture);
  //this->background.setScale(window->getSize().x, window->getSize().y);
}

Game::~Game()
{
  delete this->window;
  delete this->world;
  delete this->background_texture;
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

  // SFML
  this->window->pushGLStates();

  this->window->draw(this->background);

  this->window->popGLStates();

  // OpenGL
  this->world->Update();

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

sf::RenderWindow *Game::window = nullptr;
World *Game::world = nullptr;
float Game::dt = 0.0f;