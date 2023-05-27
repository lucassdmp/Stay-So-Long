#include "Enemy.hpp"
#include <iostream>
#include "../Util/functions.hpp"
#include "../Core/Game.hpp"
#include "../Core/World.hpp"

Enemy::Enemy(glm::vec2 pos, glm::vec2 size, sf::Color color) : Entity(5, 5, 2.0f, pos, size, color)
{
  this->type = static_cast<EnemyType>(genRandomNumberInRange(0, 3));
}

Enemy::~Enemy()
{
  bullets.clear();
}

void Enemy::fixedUpdate()
{
  // look at the player
  lookDir = World::player->getPos() - this->pos;
  lookDir = glm::normalize(lookDir);

  rotationAngle = (std::atan2(lookDir.y, lookDir.x) * 180.0f / M_PI) - 90.0f;

  handleEnemyTypes();

  update();
  draw();
}

void Enemy::handleEnemyTypes()
{
  switch(type)
  {
    case EnemyType::FOLLOWER:
      this->pos += lookDir * this->getSpeed();
      break;

    case EnemyType::CHARGER:
      handleCharger();
      break;

    case EnemyType::SHOOTER:
      handleShooter();
      break;
  }
}

void Enemy::handleCharger()
{
  if (!isCharging && !isSprinting)
  {
    // the enemy moves normally towards the player
    this->pos += lookDir * this->getSpeed();

    // if the enemy has been moving towards the player for a certain amount of time, it will charge
    chargeTimer += 0.1f;
    if (chargeTimer >= chargeDuration) 
    {
      isCharging = true;
      chargeTimer = 0.0f;
    }
  }

  if (isCharging)
  {
    // the enemy will stop and charge for a certain amount of time
    this->pos += 0.0f;
    // the enemy will charge in the direction it was moving towards the player
    chargingTimer += 0.1f;
    if (chargingTimer >= chargingDuration)
    {
      // the enemy will stop charging and sprint in the direction it was charging
      sprintDir = lookDir;
      isSprinting = true;
      isCharging = false;
      chargingTimer = 0.0f;
    }
  }

  if (isSprinting)
  {
    // the enemy will sprint in the direction it was charging
    this->pos += sprintDir * this->getSpeed() * 5.0f;
    // the enemy will sprint for a certain amount of time before returning to normal
    sprintTimer += 0.1f;
    if (sprintTimer >= sprintDuration)
    {
      isSprinting = false;
      sprintTimer = 0.0f;
      chargeTimer = 0.0f;
    }
  }
}

void Enemy::handleShooter()
{
  this->pos += lookDir * this->getSpeed() / 2.0f;

  shootCooldown += 0.1f;
  if (shootCooldown >= shootCooldownDuration)
  {
    // the enemy will shoot a bullet in the direction of the player
    glm::vec2 bulletDir = World::player->getPos() - this->pos;
    bulletDir = glm::normalize(bulletDir);

    Projectile projectile = Projectile(bulletDir, bulletSpeed, this->pos, glm::vec2(20.0f, 20.0f), sf::Color::Red);
    
    bullets.push_back(projectile);
    shootCooldown = 0.0f;
  }

  for (auto &bullet : bullets)
  {
    bullet.update();

    if (checkCollision(bullet, *World::player))
    {
      World::player->takeDamage(bulletDamage);
      bullet.setPos(glm::vec2(-100.0f, -100.0f));
    }
  }

  if (bullets.size() > 0)
  {
    auto i = std::remove_if(bullets.begin(), bullets.end(), [&](Projectile &bullet) {
      if (isOutOfBounds(bullet, *Game::window))
      {
        return true;
      }

      return false;
    });

    if (i != bullets.end())
    {
      bullets.erase(i);
    }
  }
}

void Enemy::draw()
{
  glColor3f(color.r, color.g, color.b);

  glPushMatrix();
  glTranslatef(pos.x, pos.y, 0.0f);
  glRotatef(rotationAngle, 0, 0, 1);
  glScalef(size.x, size.y, 1.0f);

  switch(type)
  {
    case EnemyType::FOLLOWER:
      glBegin(GL_QUADS);
        glVertex2f( 0.0f,  0.9f);
        glVertex2f( 0.9f,  0.0f);
        glVertex2f( 0.0f,  -0.9f);
        glVertex2f(-0.9f,  0.0f);
      glEnd();
      break;

    case EnemyType::CHARGER:
      glBegin(GL_TRIANGLES);
        glVertex2f( 0.0f,  1.0f);
        glVertex2f( 0.5f, -0.5f);
        glVertex2f(-0.5f, -0.5f);
      glEnd();
      break;

    case EnemyType::SHOOTER:
      glBegin(GL_QUADS);
        glVertex2f( 0.0f,  0.5f);
        glVertex2f( 0.5f,  0.0f);
        glVertex2f( 0.0f,  -0.5f);
        glVertex2f(-0.5f,  0.0f);
      glEnd();

      // right wing
      glBegin(GL_TRIANGLES);
        glVertex2f( 0.5f, -0.5f);
        glVertex2f( 0.9f, -0.5f);
        glVertex2f( 0.5f,  0.7f);
      glEnd();

      // left wing
      glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(-0.9f, -0.5f);
        glVertex2f(-0.5f,  0.7f);
      glEnd();
      break;
  }

  glPopMatrix();

    // draw the enemy's hitbox
/*   glColor3f(1.0f, 0.0f, 0.0f);
  glPushMatrix();
    glTranslatef(pos.x, pos.y, 0.0f);
    glScalef(size.x, size.y, 1.0f);
    Shapes::Circle(1, 16, false);
  glPopMatrix();

    // draw the enemy's center position
  glColor3f(1.0f, 1.0f, 1.0f);
  glPointSize(5.0f);
  glBegin(GL_POINTS);
    glVertex2f(pos.x, pos.y);
  glEnd(); */
}