#include "Gun.hpp"
#include <GL/gl.h>
#include "../Util/Shapes.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include "Projectile.hpp"

Gun::Gun()
{
}

Gun::~Gun()
{
}

void Gun::shoot()
{
  if (this->shot_timer < this->shot_cooldown)
    return;

  this->shot_timer = 0.0f;

  glm::vec2 direction = glm::vec2(this->mouse_pos.x - this->pos.x, this->mouse_pos.y - this->pos.y);

  // normalize direction
  float length = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
  direction.x /= length;
  direction.y /= length;
  direction *= 10.0f; // speed

  glm::vec2 bullet_start_pos = this->pos + this->offset;

  Projectile projectile = Projectile(direction, bullet_start_pos, glm::vec2(10.0f, 10.0f), sf::Color::White);

  this->projectiles.push_back(projectile);
}

void Gun::handleShots(sf::RenderWindow &window)
{
  this->shot_timer += 0.1f;
  if (this->is_shooting)
    this->shoot();

  for (unsigned int i = 0; i < this->projectiles.size(); i++)
  {
    this->projectiles[i].update();
    if (this->projectiles[i].getPos().x > window.getSize().x || this->projectiles[i].getPos().x < 0 || this->projectiles[i].getPos().y > window.getSize().y || this->projectiles[i].getPos().y < 0)
      this->projectiles.erase(this->projectiles.begin() + i);
    this->projectiles[i].draw();
  }
}

void Gun::update(glm::vec2 player_pos, sf::RenderWindow &window, Entity &player)
{
  this->handleShots(window);

  this->pos = player_pos;

  this->mouse_pos = sf::Mouse::getPosition(window);

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