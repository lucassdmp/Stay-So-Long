#include "functions.hpp"
#include <cmath>
#include <iostream>
#include <GL/gl.h>

float wave(float time, float from, float to, float duration) {
    float amplitude = (to - from) / 2.0f;
    float frequency = 1.0f / duration;
    float phase = from + amplitude;
    return amplitude * sin(2 * M_PI * frequency * time) + phase;
}

bool checkCollision(GameObject &obj1, GameObject &obj2)
{
    float distance_x = obj1.getPos().x - obj2.getPos().x;
    float distance_y = obj1.getPos().y - obj2.getPos().y;
    float length = sqrt(distance_x * distance_x + distance_y * distance_y);

    float radius1 = obj1.getSize().x / 2.0f;
    float radius2 = obj2.getSize().x / 2.0f;
    float radius_sum = radius1 + radius2;

    float distance = length - radius_sum;
    
    /* draw collision line distance between objects
    if (distance < radius_sum)
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