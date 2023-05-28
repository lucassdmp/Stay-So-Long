#pragma once

#include "GameObject.hpp"
#include <glm/vec2.hpp>

bool checkCollision(GameObject &obj1, GameObject &obj2);

bool isOutOfBounds(GameObject &obj, sf::RenderWindow &window);

glm::vec2 generateRandomPositionOutsideWindow(sf::RenderWindow &window);

float genRandomNumberInRange(float min, float max);
int genRandomNumberInRange(int min, int max);