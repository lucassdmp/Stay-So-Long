#include <GL/gl.h>
#include <cmath>
#include "Shapes.hpp"

void Shapes::Square()
{
  glBegin(GL_QUADS);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);
  glEnd();
}

void Shapes::Circle(float radius, int segments)
{
  glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0);
    for (int i = 0; i <= segments; i++)
    {
      float angle = i * 2.0f * M_PI / segments;
      glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
  glEnd();
}