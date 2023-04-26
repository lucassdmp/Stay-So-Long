#include <GL/gl.h>
#include "Game.h"
#include "../Util/Shapes.h"

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

  glViewport(0, 0, desktop.width, desktop.height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, desktop.width, 0, desktop.height, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
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
  while(this->window->isOpen())
  {
    this->Update();
    this->Render();
  }
}

void Game::Update()
{
  while(this->window->pollEvent(*this->event))
  {
    this->handleInput();
  }

  *this->deltaTime = this->clock->restart();
}

void Game::Render()
{
  this->window->clear(sf::Color::Black);

  glPushMatrix();

  glTranslatef(200, 200, 1);
  glScalef(100, 100, 1);

  Shapes::Circle();

  glPopMatrix();

  this->window->display();
}

void Game::handleInput()
{
  if(this->event->type == sf::Event::Closed)
    this->window->close();
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    this->window->close();
}