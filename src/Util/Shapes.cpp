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

void Shapes::Circle()
{
  glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0);
    for(int i = 0; i <= 360; i++)
    {
      glVertex2f(cos(i * 3.14159 / 180), sin(i * 3.14159 / 180));
    }
  glEnd();
}