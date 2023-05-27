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
  this->window = new sf::RenderWindow(sf::VideoMode(desktop.width, desktop.height), "Stay So Long", sf::Style::Fullscreen);
  this->window->setPosition(sf::Vector2i((desktop.width / 2) - (desktop.width / 2), (desktop.height / 2) - (desktop.height / 2)));
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
  float scaleX = (float)window->getSize().x / (float)background_texture->getSize().x;
  float scaleY = (float)window->getSize().y / (float)background_texture->getSize().y;
  this->background.setScale(scaleX, scaleY);

  font = new sf::Font();
  if (!font->loadFromFile("../src/Assets/Fonts/roboto.ttf"))
    std::cout << "Error loading font" << std::endl;
    
  texts.insert(std::pair<std::string, sf::Text>("score", sf::Text()));
  texts.insert(std::pair<std::string, sf::Text>("level", sf::Text()));
  texts.insert(std::pair<std::string, sf::Text>("wave", sf::Text()));

  for (auto &text : texts)
  {
    text.second.setFont(*font);
    text.second.setCharacterSize(24);
    text.second.setFillColor(sf::Color::White);
  }

  texts["score"].setPosition(15, 15);
  texts["level"].setPosition(15, 45);
  texts["wave"].setPosition(15, 75);
}

Game::~Game()
{
  delete this->window;
  delete this->world;
  delete this->background_texture;
  delete this->font;
}

void Game::Run()
{
  while (this->window->isOpen())
  {
    while (this->window->pollEvent(this->event))
    {
      this->HandleInput();
    }

    if (Input::get_key(sf::Keyboard::Escape) && world->player->getIsAlive())
    {
      isPaused = !isPaused;
      Input::set_key(sf::Keyboard::Escape, false);
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
  for (auto &text : texts)
    this->window->draw(text.second);

  this->window->popGLStates();

  // OpenGL
  if (!isPaused)
    this->world->Update();
  else
  {
    this->world->Render();
    
    this->window->pushGLStates();

    // opaque black background with SFML
    sf::RectangleShape background(sf::Vector2f(window->getSize().x, window->getSize().y));
    background.setFillColor(sf::Color(0, 0, 0, 128));
    this->window->draw(background);    

    sf::Text paused_text;
    paused_text.setFont(*font);
    paused_text.setCharacterSize(48);
    paused_text.setFillColor(sf::Color::White);
    if (!this->world->player->getIsAlive())
      paused_text.setString("Game Over");
    else
      paused_text.setString("Paused");
    paused_text.setPosition((window->getSize().x / 2) - (paused_text.getLocalBounds().width / 2), (window->getSize().y / 2) - (paused_text.getLocalBounds().height / 2));
    this->window->draw(paused_text);

    sf::Text resume_text;
    resume_text.setFont(*font);
    resume_text.setCharacterSize(24);
    resume_text.setFillColor(sf::Color::White);
    resume_text.setString("Press ESC to resume");
    resume_text.setPosition((window->getSize().x / 2) - (resume_text.getLocalBounds().width / 2), (window->getSize().y / 2) - (resume_text.getLocalBounds().height / 2) + 48);
    if (this->world->player->getIsAlive())
      this->window->draw(resume_text);

    sf::Text restart_text;
    restart_text.setFont(*font);
    restart_text.setCharacterSize(24);
    restart_text.setFillColor(sf::Color::White);
    restart_text.setString("Press R to restart");
    restart_text.setPosition((window->getSize().x / 2) - (restart_text.getLocalBounds().width / 2), (window->getSize().y / 2) - (restart_text.getLocalBounds().height / 2) + 96);
    this->window->draw(restart_text);

    sf::Text quit_text;
    quit_text.setFont(*font);
    quit_text.setCharacterSize(24);
    quit_text.setFillColor(sf::Color::White);
    quit_text.setString("Press Q to quit");
    quit_text.setPosition((window->getSize().x / 2) - (quit_text.getLocalBounds().width / 2), (window->getSize().y / 2) - (quit_text.getLocalBounds().height / 2) + 144);
    this->window->draw(quit_text);

    if (Input::get_key(sf::Keyboard::R))
    {
      Resume();
      this->world->restartGame();
      Input::set_key(sf::Keyboard::R, false);
    }

    this->window->popGLStates();
  }

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
    if (this->event.key.code == sf::Keyboard::Q)
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

void Game::Pause()
{
  isPaused = true;
}

void Game::Resume()
{
  isPaused = false;
}

bool Game::isPaused = false;
sf::RenderWindow *Game::window = nullptr;
World *Game::world = nullptr;
float Game::dt = 0.0f;
std::map<std::string, sf::Text> Game::texts;