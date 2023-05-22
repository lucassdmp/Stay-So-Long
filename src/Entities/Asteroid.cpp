#include "Asteroid.hpp"
#include "../Core/Game.hpp"
#include "../Util/functions.hpp"

Asteroid::Asteroid(glm::vec2 playerPos, glm::vec2 size) : Entity(10, 10, 2.0f, glm::vec2(0.0f, 0.0f), size, sf::Color::Red)
{
  generateVertices();
  setDirectionAndInitialPosition(playerPos);
}

Asteroid::~Asteroid()
{
}

void Asteroid::move()
{
  // count how long the asteroid has been out of bounds
  if (isOutOfBounds(*this, *Game::window))
    outOfBoundsTimer += 0.1f;
  else
    outOfBoundsTimer = 0.0f;
  
  rotationAngle += 1.0f;
  if (rotationAngle > 360.0f)
    rotationAngle = 0.0f;

  pos += direction * this->getSpeed();

  draw();
}

void Asteroid::setDirectionAndInitialPosition(glm::vec2 playerPos)
{
  glm::vec2 asteroidInitialPos = generateRandomPositionOutsideWindow(*Game::window);
  // direction is a vector from the asteroid to the last position of the player
  direction = playerPos - asteroidInitialPos;
  direction = glm::normalize(direction);
  pos = asteroidInitialPos;
}

void Asteroid::generateVertices()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-1.0f, 1.0f);

  float radius = 1.0f;
  int numVertices = 10;

  for (unsigned int i = 0; i < numVertices; i++)
  {
    float angle = (2 * M_PI * i) / numVertices;
    angle += dis(gen);
    float x = radius * cos(angle);
    float y = radius * sin(angle);

    float offset = radius * 0.1;
    float normalX = -sin(angle);
    float normalY = cos(angle);
    x += offset * normalX;
    y += offset * normalY;

    vertices.push_back(glm::vec2(x, y));
  }
}

void Asteroid::draw()
{
  // draw the asteroid's hitbox
  /* glColor3f(1.0f, 0.0f, 0.0f);
  glPushMatrix();
    glTranslatef(pos.x, pos.y, 0.0f);
    glScalef(size.x, size.y, 1.0f);
    Shapes::Circle(1, 16, false);
  glPopMatrix(); */

  // draw the outer asteroid polygon
  glPushMatrix();
    glColor3f(0.4f, 0.4f, 0.4f);
    glTranslatef(pos.x, pos.y, 0.0f);
    glRotatef(rotationAngle, 0, 0, 1);
    glScalef(size.x, size.y, 1.0f);
    glBegin(GL_POLYGON);
    for (unsigned int i = 0; i < vertices.size(); i++)
    {
      glVertex2f(vertices[i].x, vertices[i].y);
    }
    glEnd();

  glPopMatrix();

  // draw the inner asteroid polygon
  glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f);
    glTranslatef(pos.x, pos.y, 0.0f);
    glRotatef(rotationAngle, 0, 0, 1);
    glScalef(size.x - size.x / 3, size.y - size.y / 3, 1.0f);
    glBegin(GL_POLYGON);
    for (unsigned int i = 0; i < vertices.size(); i++)
    {
      glVertex2f(vertices[i].x, vertices[i].y);
    }
    glEnd();
  glPopMatrix();

  // draw the asteroid's center position
  /* glColor3f(1.0f, 1.0f, 1.0f);
  glPointSize(5.0f);
  glBegin(GL_POINTS);
    glVertex2f(pos.x, pos.y);
  glEnd(); */
}