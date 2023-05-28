#include "Entity.hpp"

Entity::Entity(int max_health, int current_health, float speed, glm::vec2 pos, glm::vec2 size, sf::Color color) :
 GameObject(pos, size, color)
{
    this->max_health = max_health;
    this->current_health = current_health;
    this->speed = speed;
    this->isAlive = true;
}

Entity::Entity() : GameObject()
{
    this->max_health = 0;
    this->current_health = 0;
    this->speed = 0;
    this->isAlive = true;
}

void Entity::update()
{
    if (this->current_health <= 0)
        this->isAlive = false;
}

