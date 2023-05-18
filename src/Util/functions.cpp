#include "functions.hpp"
#include <cmath>

float wave(float time, float from, float to, float duration) {
    float amplitude = (to - from) / 2.0f;
    float frequency = 1.0f / duration;
    float phase = from + amplitude;
    return amplitude * sin(2 * M_PI * frequency * time) + phase;
}

bool checkCollision(GameObject &obj1, GameObject &obj2)
{
    glm::vec2 leftBottom = obj1.getPos();
    glm::vec2 rightTop = obj1.getPos() + obj1.getSize();

    glm::vec2 obj2LeftBottom = obj2.getPos();
    glm::vec2 obj2RightTop = obj2.getPos() + obj2.getSize();

    return leftBottom.x < obj2RightTop.x && rightTop.x > obj2LeftBottom.x &&
           leftBottom.y < obj2RightTop.y && rightTop.y > obj2LeftBottom.y;
}