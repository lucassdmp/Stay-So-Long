#include "Gun.hpp"
#include <GL/gl.h>
#include "../Util/Shapes.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

Gun::Gun()
{
}

Gun::Gun(glm::vec2 initial_pos)
{
}

Gun::~Gun()
{
}

void Gun::shoot()
{
}

void Gun::update(glm::vec2 player_pos, sf::RenderWindow &window)
{
  this->pos = player_pos;

  sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

  float adjacent = mouse_pos.x - this->pos.x;
  float opposite = mouse_pos.y - this->pos.y;

  float hip = sqrt(pow(adjacent, 2) + pow(opposite, 2));

  if (mouse_pos.y < this->pos.y)
    this->angle = -acos(adjacent / hip) * 180 / M_PI;
  else
    this->angle = acos(adjacent / hip) * 180 / M_PI;
}

void Gun::draw()
{
  glPushMatrix();
    // translate the gun to the player's center
    glTranslatef(this->pos.x, this->pos.y, 0.0f);

    // rotate around the base of the gun
    glRotatef(this->angle, 0.0f, 0.0f, 1.0f);

    // translate to the base of the gun to rotate around the base not the center
    glTranslatef(40.0f, 0.0f, 0.0f);

    glScalef(40.0f, 10.0f, 1.0f);
    
    glColor3f(1.0f, 1.0f, 0.0f);
    
    Shapes::Square();
  glPopMatrix();
}