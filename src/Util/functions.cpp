#include "functions.hpp"
#include <cmath>
#include <iostream>
#include <GL/gl.h>
#include <random>

bool checkCollision(GameObject &obj1, GameObject &obj2)
{
    float distance_x = obj1.getPos().x - obj2.getPos().x;
    float distance_y = obj1.getPos().y - obj2.getPos().y;
    float length = sqrt(distance_x * distance_x + distance_y * distance_y);

    float radius1 = obj1.getSize().x / 2.0f;
    float radius2 = obj2.getSize().x / 2.0f;
    float radius_sum = radius1 + radius2;

    float distance = length - radius_sum;
    
    // draw collision line distance between objects
    /* if (distance < radius_sum)
        glColor3f(1.0f, 0.0f, 0.0f);
    else
        glColor3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_LINES);
        glVertex2f(obj1.getPos().x, obj1.getPos().y);
        glVertex2f(obj2.getPos().x, obj2.getPos().y);
    glEnd(); */
    
    return distance < radius_sum;
}

bool isOutOfBounds(GameObject &obj, sf::RenderWindow &window)
{
    return obj.getPos().x < 0 || obj.getPos().x > window.getSize().x ||
           obj.getPos().y < 0 || obj.getPos().y > window.getSize().y;
}

glm::vec2 generateRandomPositionOutsideWindow(sf::RenderWindow &window)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0f, 1.0f);

  glm::vec2 pos;
  if (std::round(dis(gen)) == 0)
  {
    // choose a random y between 0 and window.getSize().y
    float y = dis(gen) * window.getSize().y;

    // pick 0 or window.getSize().x
    float x = std::round(dis(gen)) == 0 ? 0 : window.getSize().x;

    pos = glm::vec2(x, y);
  }
  else
  {
    // choose a random x between 0 and window.getSize().x
    float x = dis(gen) * window.getSize().x;

    // pick 0 or window.getSize().y
    float y = std::round(dis(gen)) == 0 ? 0 : window.getSize().y;

    pos = glm::vec2(x, y);
  }

  return pos;
}

float genRandomNumberInRange(float min, float max)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(min, max);
  return dis(gen);
}

int genRandomNumberInRange(int min, int max)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(min, max);
  return dis(gen);
}