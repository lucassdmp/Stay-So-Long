#include "Enemy.hpp"

Enemy::Enemy(glm::vec2 pos, glm::vec2 size, sf::Color color) : Entity(5, 5, 2.0f, pos, size, color)
{
}

Enemy::~Enemy()
{
}

void Enemy::fixedUpdate(glm::vec2 playerPos)
{
    // follow the player
  glm::vec2 dir = playerPos - this->pos;
  dir = glm::normalize(dir);

  rotationAngle = (std::atan2(dir.y, dir.x) * 180.0f / M_PI) - 90.0f;

  this->pos += dir * this->getSpeed();
  
  update();
  draw();
}

void Enemy::draw()
{
  glPushMatrix();
  glColor3f(color.r, color.g, color.b);
  glTranslatef(pos.x, pos.y, 0.0f);
  glRotatef(rotationAngle, 0, 0, 1);
  glScalef(size.x, size.y, 1.0f);

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

  glPopMatrix();

    // draw the enemy's hitbox
  /* glColor3f(1.0f, 0.0f, 0.0f);
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