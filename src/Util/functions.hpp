#pragma once

#include "GameObject.hpp"
#include <glm/vec2.hpp>

float wave(float time, float from, float to, float duration);

bool checkCollision(GameObject &obj1, GameObject &obj2);

bool isOutOfBounds(GameObject &obj, sf::RenderWindow &window);

glm::vec2 generateRandomPositionOutsideWindow(sf::RenderWindow &window);