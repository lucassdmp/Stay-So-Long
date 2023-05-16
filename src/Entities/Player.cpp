#include "Player.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../Util/functions.hpp"
#include <iostream>
#include "../Util/Input.hpp"
#include <cmath>

Player::Player(int max_health, int current_health, float speed, glm::vec2 pos, glm::vec2 size, sf::Color color) : 
    Entity(max_health, current_health, speed, pos, size, color) {
}

Player::Player() : Entity() {}

void Player::fixedUpdate(float dt, sf::RenderWindow &window)
{
    if (Input::get_key(sf::Keyboard::W))
        this->pos.y -= this->getSpeed();
    if (Input::get_key(sf::Keyboard::A))
        this->pos.x -= this->getSpeed();
    if (Input::get_key(sf::Keyboard::S))
        this->pos.y += this->getSpeed();
    if (Input::get_key(sf::Keyboard::D))
        this->pos.x += this->getSpeed();

    glm::vec2 lookDir = (Input::mouse_pos - this->pos);
    lookDir = glm::normalize(lookDir);
    angle = (atan2(lookDir.y, lookDir.x) * 180 / M_PI) - 90.0f;

    this->update();
    this->handleShots(window);
    this->draw(dt, window);
}

void Player::move()
{

}

void Player::handleShots(sf::RenderWindow &window)
{
  this->shot_timer += 0.1f;
  if (Input::get_mouse_button(sf::Mouse::Left))
    this->shoot();

  for (unsigned int i = 0; i < this->projectiles.size(); i++)
  {
    this->projectiles[i].update();
    if (this->projectiles[i].getPos().x > window.getSize().x || this->projectiles[i].getPos().x < 0 || this->projectiles[i].getPos().y > window.getSize().y || this->projectiles[i].getPos().y < 0)
      this->projectiles.erase(this->projectiles.begin() + i);
    this->projectiles[i].draw();
  }
}

void Player::shoot()
{
  if (this->shot_timer < this->shot_cooldown)
    return;

  this->shot_timer = 0.0f;

  glm::vec2 direction = glm::vec2(Input::mouse_pos.x - this->pos.x, Input::mouse_pos.y - this->pos.y);

  // normalize direction
  float length = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
  direction.x /= length;
  direction.y /= length;
  direction *= 10.0f; // speed

  glm::vec2 bullet_start_pos = this->pos;

  Projectile projectile = Projectile(direction, bullet_start_pos, glm::vec2(10.0f, 10.0f), sf::Color::White);

  this->projectiles.push_back(projectile);
}

void Player::draw(float dt, sf::RenderWindow &window)
{
    glColor3f(this->color.r, this->color.g, this->color.b);
    glPushMatrix();
    glTranslatef(this->pos.x, this->pos.y, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glScalef(this->size.x, this->size.y, 1.0f);
    
        // spaceship body
        glBegin(GL_POLYGON);
            glVertex2f(-0.3f, 0.5f); // A
            glVertex2f(-0.7f, -0.5f); // B
            glVertex2f(-0.5f, -1.0f); // C
            glVertex2f(-0.5f, -1.3f); // D
            glVertex2f( 0.0f, -1.5f); // E
            glVertex2f(+0.5f, -1.3f); // F
            glVertex2f(+0.5f, -1.0f); // G
            glVertex2f(+0.7f, -0.5f); // H
            glVertex2f(+0.3f, 0.5f); // I
        glEnd();

        // spaceship right wing
        glBegin(GL_POLYGON);
            glVertex2f(-0.85f, -0.7f);
            glVertex2f(-0.7f, -1.0f);
            glVertex2f(-0.7f, -1.3f);
            glVertex2f(-1.5f, -1.5f);
            glVertex2f(-1.7f, -1.3f);
        glEnd();

        // spaceship right wing mirrored
        glScalef(-1.0f, 1.0f, 1.0f);
        glBegin(GL_POLYGON);
            glVertex2f(-0.85f, -0.7f);
            glVertex2f(-0.7f, -1.0f);
            glVertex2f(-0.7f, -1.3f);
            glVertex2f(-1.5f, -1.5f);
            glVertex2f(-1.7f, -1.3f);
        glEnd();

    glPopMatrix();
}
