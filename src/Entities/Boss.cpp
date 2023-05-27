#include "Boss.hpp"
#include "../Util/functions.hpp"
#include "../Core/Game.hpp"
#include "../Core/World.hpp"
#include <glm/gtc/matrix_transform.hpp>

#define HEALTH_BAR_HEIGHT 10

Boss::Boss(glm::vec2 pos, glm::vec2 size, sf::Color color) : Entity(300, 300, 2.0f, pos, size, color)
{
  shootTimerMax = 0.5f;
  shootTimer = shootTimerMax;
}

Boss::~Boss()
{
  projectiles.clear();
}

void Boss::update()
{
  if (checkCollision(*this, *World::player))
  {
    World::player->takeDamage(5);
    float distance = glm::distance(pos, World::player->getPos());

    glm::vec2 direction = glm::normalize(pos - World::player->getPos());

    World::player->setPos(World::player->getPos() - direction * (World::player->getSpeed() * 2.0f));
  }

  // move to center
  if (pos.y != Game::window->getSize().y / 2.0f)
  {
    pos.y += getSpeed();
  }
  // shoot and rotate if in center
  else 
  {
    rotation += 0.5f;
    if (rotation > 360.0f)
      rotation = 0.0f;

    shootTimer -= 0.1f;
    if (shootTimer <= 0.0f)
    {
      shoot();
      shootTimer = shootTimerMax;
    }
  }

  for (auto &projectile : projectiles)
  {
    projectile.update();

    if (checkCollision(projectile, *World::player))
    {
      World::player->takeDamage(1);
      projectile.setPos(glm::vec2(-100.0f, -100.0f));
    }
  }

  if (projectiles.size() > 0)
  {
    auto i = std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile &projectile) {
      if (isOutOfBounds(projectile, *Game::window))
        return true;

      return false;
    });

    if (i != projectiles.end())
    {
      projectiles.erase(i);
    }
  }

  draw();
}

void Boss::shoot()
{
  glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

  glm::vec4 projPos1 = glm::vec4(size.x, 0.0f, 0.0f, 1.0f);
  projPos1 = rotationMat * projPos1;
  glm::vec4 projPos2 = glm::vec4(-size.x, 0.0f, 0.0f, 1.0f);
  projPos2 = rotationMat * projPos2;
  glm::vec4 projPos3 = glm::vec4(0.0f, size.y, 0.0f, 1.0f);
  projPos3 = rotationMat * projPos3;
  glm::vec4 projPos4 = glm::vec4(0.0f, -size.y, 0.0f, 1.0f);
  projPos4 = rotationMat * projPos4;

  glm::vec2 finalProjPos1 = pos + glm::vec2(projPos1);
  glm::vec2 finalProjPos2 = pos + glm::vec2(projPos2);
  glm::vec2 finalProjPos3 = pos + glm::vec2(projPos3);
  glm::vec2 finalProjPos4 = pos + glm::vec2(projPos4);

  // direction is the same as the rotation of the boss
  glm::vec2 direction1 = glm::vec2(projPos1);
  direction1 = glm::normalize(direction1);
  glm::vec2 direction2 = glm::vec2(projPos2);
  direction2 = glm::normalize(direction2);
  glm::vec2 direction3 = glm::vec2(projPos3);
  direction3 = glm::normalize(direction3);
  glm::vec2 direction4 = glm::vec2(projPos4);
  direction4 = glm::normalize(direction4);

  Projectile projectile1 = Projectile(direction1, 3.0f, finalProjPos1, glm::vec2(10.0f, 10.0f), sf::Color::White);
  Projectile projectile2 = Projectile(direction2, 3.0f, finalProjPos2, glm::vec2(10.0f, 10.0f), sf::Color::White);
  Projectile projectile3 = Projectile(direction3, 3.0f, finalProjPos3, glm::vec2(10.0f, 10.0f), sf::Color::White);
  Projectile projectile4 = Projectile(direction4, 3.0f, finalProjPos4, glm::vec2(10.0f, 10.0f), sf::Color::White);

  projectiles.push_back(projectile1);
  projectiles.push_back(projectile2);
  projectiles.push_back(projectile3);
  projectiles.push_back(projectile4);
}

void Boss::draw()
{
  drawHealthBar();

  glPushMatrix();
  glTranslatef(pos.x, pos.y, 0.0f);
  glRotatef(rotation, 0.0f, 0.0f, 1.0f);
  glScalef(size.x, size.y, 1.0f);

  glColor3f(color.r, color.g, color.b);

  Shapes::Circle(1.0f, 36);

  glPopMatrix();

  glPushMatrix();
  glColor3f(1.0f, 1.0f, 1.0f);
  glTranslatef(pos.x, pos.y, 0.0f);
  glRotatef(rotation, 0.0f, 0.0f, 1.0f);
  glTranslatef(size.x, 0.0f, 0.0f);
  glScalef(20.0f, 10.0f, 1.0f);

  Shapes::Square();

  glPopMatrix();

  glPushMatrix();
  glColor3f(1.0f, 1.0f, 1.0f);
  glTranslatef(pos.x, pos.y, 0.0f);
  glRotatef(rotation, 0.0f, 0.0f, 1.0f);
  glTranslatef(-size.x, 0.0f, 0.0f);
  glScalef(20.0f, 10.0f, 1.0f);

  Shapes::Square();

  glPopMatrix();

  glPushMatrix();
  glColor3f(1.0f, 1.0f, 1.0f);
  glTranslatef(pos.x, pos.y, 0.0f);
  glRotatef(rotation, 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, size.y, 0.0f);
  glScalef(10.0f, 20.0f, 1.0f);

  Shapes::Square();

  glPopMatrix();

  glPushMatrix();
  glColor3f(1.0f, 1.0f, 1.0f);
  glTranslatef(pos.x, pos.y, 0.0f);
  glRotatef(rotation, 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, -size.y, 0.0f);
  glScalef(10.0f, 20.0f, 1.0f);

  Shapes::Square();

  glPopMatrix();
}

void Boss::drawHealthBar()
{
    glColor3f(0.77f, 0.31f, 0.31f);
    glPushMatrix();
    glTranslatef(Game::window->getSize().x / 2, HEALTH_BAR_HEIGHT + 10.0f, 0.0f);
    glScalef(this->getMaxHealth(), HEALTH_BAR_HEIGHT, 1.0f);
    Shapes::Square();
    glPopMatrix();

    glColor3f(1.0f, 0.42f, 0.42f);
    glPushMatrix();
    glTranslatef(Game::window->getSize().x / 2, HEALTH_BAR_HEIGHT + 10.0f, 0.0f);
    glScalef(this->getCurrentHealth(), HEALTH_BAR_HEIGHT, 1.0f);

    Shapes::Square();

    glPopMatrix();
}