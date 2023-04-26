#include <GL/gl.h>
#include "Game.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 720

Game::Game()
{
  this->window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Stay So Long", sf::Style::Fullscreen);
  this->event = new sf::Event();
  this->clock = new sf::Clock();
  this->time = new sf::Time();
  this->deltaTime = new sf::Time();

  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, 0.0f, 1.0f);
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
    this->HandleInput();
  }

  *this->deltaTime = this->clock->restart();
}

void Game::Render()
{
  this->window->clear(sf::Color::Black);

  glBegin(GL_QUADS);
    glVertex2f(-200, -200);
    glVertex2f(200, -200);
    glVertex2f(200, 200);
    glVertex2f(-200, 200);
  glEnd();

  this->window->display();
}

void Game::HandleInput()
{
  if(this->event->type == sf::Event::Closed)
    this->window->close();
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    this->window->close();
}