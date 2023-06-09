#include "Player.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../Util/functions.hpp"
#include <iostream>
#include "../Util/Input.hpp"
#include <cmath>
#include <algorithm>
#include "../Core/World.hpp"
#include "../Core/Game.hpp"

#define HEALTH_BAR_HEIGHT 10.0f

Player::Player(int max_health, int current_health, float speed, glm::vec2 pos, glm::vec2 size, sf::Color color) : 
    Entity(max_health, current_health, speed, pos, size, color) {
}

Player::Player() : Entity() {}

void Player::fixedUpdate(float dt, sf::RenderWindow &window)
{    
    lookDir = (Input::mouse_pos - this->pos);
    lookDir = glm::normalize(lookDir);
    angle = (atan2(lookDir.y, lookDir.x) * 180 / M_PI) - 90.0f;

    handleUpgrades();

    this->move(dt);
    this->checkBounds(window);
    this->update();
    this->handleShots(window);
    this->draw(dt, window);
}

void Player::handleUpgrades()
{
    if (World::score >= this->next_level_up_score && this->current_level < this->max_level)
    {
        next_level_up_score += 50 * this->current_level;
        this->current_level++;
        shot_cooldown = shot_cooldown / (this->current_level * 0.5f);
        shot_cooldown = std::max(shot_cooldown, min_shot_cooldown);
        this->setMaxHealth(this->getMaxHealth() + 50);
        this->setCurrentHealth(this->getMaxHealth());
    }
    Game::texts["level"].setString("Level: " + std::to_string(this->current_level));
}

void Player::move(float dt)
{
    // acceleration
    if (Input::get_mouse_button(sf::Mouse::Right))
        this->velocity += lookDir * this->acceleration;

    // is the player moving right
    if (this->velocity.x > 0.0f)
    {
        // max velocity check x positive
        if (this->velocity.x > this->max_speed)
            this->velocity.x = this->max_speed;

        // deceleration
        this->velocity.x -= this->deceleration;
        if (this->velocity.x < 0.0f)
            this->velocity.x = 0.0f;
    }
    else if (this->velocity.x < 0.0f) // is the player moving left
    {
        // max velocity check x negative
        if (this->velocity.x < -this->max_speed)
            this->velocity.x = -this->max_speed;

        // deceleration
        this->velocity.x += this->deceleration;
        if (this->velocity.x > 0.0f)
            this->velocity.x = 0.0f;
    }

    if (this->velocity.y > 0.0f) // is the player moving down
    {
        // max velocity check y positive
        if (this->velocity.y > this->max_speed)
            this->velocity.y = this->max_speed;

        // deceleration
        this->velocity.y -= this->deceleration;
        if (this->velocity.y < 0.0f)
            this->velocity.y = 0.0f;
    }
    else if (this->velocity.y < 0.0f) // is the player moving up
    {
        // max velocity check y negative
        if (this->velocity.y < -this->max_speed)
            this->velocity.y = -this->max_speed;

        // deceleration
        this->velocity.y += this->deceleration;
        if (this->velocity.y > 0.0f)
            this->velocity.y = 0.0f;
    }


    this->pos += this->velocity * dt;
}

void Player::handleShots(sf::RenderWindow &window)
{
  this->shot_timer += 0.1f;
  if (Input::get_mouse_button(sf::Mouse::Left) && this->shot_timer >= this->shot_cooldown)
  {
    this->shoot();
    this->shot_timer = 0.0f;
  }

  std::vector<Asteroid> new_asteroids;

  for (auto &projectile : projectiles)
  {
    projectile.update();

    if (World::boss != nullptr)
    {
        if (checkCollision(projectile, *World::boss))
        {
            World::boss->takeDamage(10);
            projectile.setPos(glm::vec2(-100.0f, -100.0f));
        }
    }

    for (auto &asteroid : World::asteroids)
    {
        if (checkCollision(projectile, asteroid))
        {
            if (asteroid.getSize().x >= 40.0f)
            {
                new_asteroids.push_back(Asteroid(asteroid.getPos(), asteroid.getSize() / 2.0f, asteroid.getDirection()));
                new_asteroids.push_back(Asteroid(asteroid.getPos(), asteroid.getSize() / 2.0f, asteroid.getDirection()));
            }

            asteroid.setPos(glm::vec2(-100.0f, -100.0f));
            projectile.setPos(glm::vec2(-100.0f, -100.0f));
        
            World::score += 10;
        }
    }

    for (auto &enemy : World::enemies)
    {
        if (checkCollision(projectile, enemy))
        {
            enemy.takeDamage(2);
            projectile.setPos(glm::vec2(-100.0f, -100.0f));
        }
    }
  }
  
  if (projectiles.size() > 0)
  {
    auto i = std::remove_if(projectiles.begin(), projectiles.end(), [&](GameObject o) {
      return isOutOfBounds(o, window);
    });

    if (i != projectiles.end())
      projectiles.erase(i);
  }

  if (new_asteroids.size() > 0)
  {
    World::asteroids.insert(World::asteroids.end(), new_asteroids.begin(), new_asteroids.end());
  }
}

void Player::shoot()
{
  glm::vec2 direction = glm::vec2(Input::mouse_pos.x - this->pos.x, Input::mouse_pos.y - this->pos.y);
  direction = glm::normalize(direction);

  std::vector<Projectile> new_projectiles;

  if (current_level >= 1 && current_level < 4)
  {
    new_projectiles.push_back(Projectile(direction, 10.0f, this->pos, glm::vec2(10.0f, 10.0f), sf::Color::Yellow));
  }
  else if (current_level >= 4 && current_level < 7)
  {
    float offsetX = 15.0f;
    float offsetY = 10.0f;
    glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::vec4 projPos1 = glm::vec4(offsetX, offsetY, 0.0f, 1.0f);
    glm::vec4 projPos2 = glm::vec4(-offsetX, offsetY, 0.0f, 1.0f);
    projPos1 = rotationMat * projPos1;
    projPos2 = rotationMat * projPos2;

    glm::vec2 finalPosition1 = pos + glm::vec2(projPos1);
    glm::vec2 finalPosition2 = pos + glm::vec2(projPos2);

    new_projectiles.push_back(Projectile(direction, 10.0f, finalPosition1, glm::vec2(10.0f, 10.0f), sf::Color::Yellow));
    new_projectiles.push_back(Projectile(direction, 10.0f, finalPosition2, glm::vec2(10.0f, 10.0f), sf::Color::Yellow));
  }
  else
  {
    float offsetX = 15.0f;
    float offsetY = 10.0f;
    glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::vec4 projPos1 = glm::vec4(offsetX, offsetY, 0.0f, 1.0f);
    glm::vec4 projPos2 = glm::vec4(-offsetX, offsetY, 0.0f, 1.0f);
    projPos1 = rotationMat * projPos1;
    projPos2 = rotationMat * projPos2;

    glm::vec2 finalPosition1 = pos + glm::vec2(projPos1);
    glm::vec2 finalPosition2 = pos + glm::vec2(projPos2);

    new_projectiles.push_back(Projectile(direction, 10.0f, finalPosition1, glm::vec2(10.0f, 10.0f), sf::Color::Yellow));
    new_projectiles.push_back(Projectile(direction, 10.0f, finalPosition2, glm::vec2(10.0f, 10.0f), sf::Color::Yellow));
    new_projectiles.push_back(Projectile(direction, 10.0f, this->pos, glm::vec2(10.0f, 10.0f), sf::Color::Yellow));
  }

  projectiles.insert(projectiles.end(), new_projectiles.begin(), new_projectiles.end());
} 

void Player::checkBounds(sf::RenderWindow &window)
{
    // check if the player is out of bounds and if so, wrap them around to the other side
    if (this->pos.x < 0.0f)
        this->pos.x = window.getSize().x;
    if (this->pos.x > window.getSize().x)
        this->pos.x = 0.0f;
    if (this->pos.y < 0.0f)
        this->pos.y = window.getSize().y;
    if (this->pos.y > window.getSize().y)
        this->pos.y = 0.0f;
}

void Player::draw(float dt, sf::RenderWindow &window)
{
    drawHealthBar();
    drawCrosshair();

    glColor3f(this->color.r, this->color.g, this->color.b);
    glPushMatrix();
    glTranslatef(this->pos.x, this->pos.y, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glScalef(this->size.x, this->size.y, 1.0f);
    glTranslatef(0.0f, 0.5f, 0.0f);
    
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

        /* // draw the player's collision circle for debugging
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
        glTranslatef(pos.x, pos.y, 0.0f);
        glScalef(size.x, size.y, 1.0f);
        Shapes::Circle(1, 16, false);
    glPopMatrix(); */

/*  // draw the player's center position for debugging
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glVertex2f(this->pos.x, this->pos.y);
    glEnd(); */
}

void Player::drawCrosshair()
{
  glColor3f(1.0f, 1.0f, 1.0f);
  // crosshair circle outline
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glPushMatrix();
    glTranslatef(Input::mouse_pos.x, Input::mouse_pos.y, 0.0f);
    Shapes::Circle(16.0f, 10, false);
  glPopMatrix();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // crosshair lines and middle dot
  for (int i = 0; i < 4; i++)
  {
    glPushMatrix();
      glTranslatef(Input::mouse_pos.x, Input::mouse_pos.y, 0.0f);
      glRotatef(i * 90.0f, 0.0f, 0.0f, 1.0f);
      glTranslatef(0.0f, 10.0f, 0.0f);
      glScalef(1.0f, 5.0f, 1.0f);
      Shapes::Square();
    glPopMatrix();
  }
  glPushMatrix();
    glTranslatef(Input::mouse_pos.x, Input::mouse_pos.y, 0.0f);
    glScalef(1.0f, 1.0f, 1.0f);
    Shapes::Square();
  glPopMatrix();
}

void Player::drawHealthBar()
{   
    glColor3f(0.77f, 0.31f, 0.31f);
    glPushMatrix();
    glTranslatef(Game::window->getSize().x / 2, Game::window->getSize().y - HEALTH_BAR_HEIGHT - 10.0f, 0.0f);
    glScalef(this->getMaxHealth(), HEALTH_BAR_HEIGHT, 1.0f);
    Shapes::Square();
    glPopMatrix();

    glColor3f(1.0f, 0.42f, 0.42f);
    glPushMatrix();
    glTranslatef(Game::window->getSize().x / 2, Game::window->getSize().y - HEALTH_BAR_HEIGHT - 10.0f, 0.0f);
    glScalef(this->getCurrentHealth(), HEALTH_BAR_HEIGHT, 1.0f);

    Shapes::Square();

    glPopMatrix();
}