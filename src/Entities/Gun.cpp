#include "Gun.hpp"
#include <GL/gl.h>
#include "../Util/Shapes.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

Gun::Gun()
{
}

Gun::~Gun()
{
}

void Gun::shoot()
{
}

void Gun::update(glm::vec2 player_pos, sf::RenderWindow &window, Entity &player)
{
  this->pos = player_pos;

  sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

  float adjacent = mouse_pos.x - this->pos.x;
  float opposite = mouse_pos.y - this->pos.y;
  float hip = sqrt(pow(adjacent, 2) + pow(opposite, 2));

  // invert angle if mouse is on below of the player
  if (mouse_pos.y < this->pos.y)
    this->angle = -acos(adjacent / hip) * 180 / M_PI;
  else
    this->angle = acos(adjacent / hip) * 180 / M_PI;

  // set the gun position based on the angle and the player looking direction
  if (this->angle > 45.0f && this->angle < 135.0f)
  {
    player.setLookingAt(Direction::DOWN);
    this->offset.x = 0.0f;
    this->offset.y = 40.0f;
  }
  else if (this->angle > 135.0f || this->angle < -135.0f)
  {
    player.setLookingAt(Direction::LEFT);
    this->offset.x = -30.0f;
    this->offset.y = 0.0f;
  }
  else if (this->angle > -135.0f && this->angle < -45.0f)
  {
    player.setLookingAt(Direction::UP);
    this->offset.x = 0.0f;
    this->offset.y = -20.0f;
  }
  else if (this->angle > -45.0f && this->angle < 45.0f)
  {
    player.setLookingAt(Direction::RIGHT);
    this->offset.x = 30.0f;
    this->offset.y = 0.0f;
  }

  this->draw();
}

void Gun::draw()
{
  glPushMatrix();
    // translate the gun to the player's center
    glTranslatef(this->pos.x + this->offset.x, this->pos.y + offset.y, 0.0f);

    // rotate around the base of the gun
    glRotatef(this->angle, 0.0f, 0.0f, 1.0f);

    // translate to the base of the gun to rotate around the base not the center
    glTranslatef(20.0f, 0.0f, 0.0f);

    glScalef(20.0f, 5.0f, 1.0f);
    
    glColor3f(1.0f, 1.0f, 0.0f);
    
    Shapes::Square();
  glPopMatrix();
}