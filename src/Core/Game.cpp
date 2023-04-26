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

  glViewport(0, 0, desktop.width, desktop.height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, desktop.width, 0, desktop.height, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  window->setFramerateLimit(60);


  player = Player(100, 100, 0.2, glm::vec2(100, 100), glm::vec2(25, 55), sf::Color::Red);
}

Game::~Game()
{
  delete this->window;
  delete this->event;
  delete this->clock;
  delete this->time;
  delete this->deltaTime;
}

void Game::Run(){
  while(this->window->isOpen()){
    while(this->window->pollEvent(*this->event)){
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

  this->window->display();
}

void Game::HandleInput()
{
  if(this->event->type == sf::Event::Closed)
    this->window->close();
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    this->window->close();
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    this->player.move(glm::vec2(0, this->player.getSpeed()));
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    this->player.move(glm::vec2(0, -this->player.getSpeed()));
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    this->player.move(glm::vec2(this->player.getSpeed(), 0));
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    this->player.move(glm::vec2(-this->player.getSpeed(), 0));
  
}