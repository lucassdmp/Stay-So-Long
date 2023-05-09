#include "Entity.hpp"

Entity::Entity(int max_health, int current_health, float speed,
               glm::vec2 pos, glm::vec2 size, sf::Color color) : GameObject(pos, size, color)
{
    this->max_health = max_health;
    this->current_health = current_health;
    this->speed = speed;
    this->looking_at = Direction::DOWN;
    this->movingUp = false;
    this->movingDown = false;
    this->movingLeft = false;
    this->movingRight = false;
    this->isAlive = true;
}

Entity::Entity() : GameObject()
{
    this->max_health = 0;
    this->current_health = 0;
    this->speed = 0;
    this->looking_at = Direction::DOWN;
    this->movingUp = false;
    this->movingDown = false;
    this->movingLeft = false;
    this->movingRight = false;
    this->isAlive = true;
}

void Entity::update()
{
    if (this->current_health <= 0)
    {
        this->isAlive = false;
    }

    if (this->current_health < this->max_health)
    {
        this->color.b = (float)(this->max_health - this->current_health);
    }

    // Movement Logic
    if (this->movingUp)
    {
        this->pos.y -= this->getSpeed();
    }
    if (this->movingDown)
    {
        this->pos.y += this->getSpeed();
    }
    if (this->movingLeft)
    {
        this->pos.x -= this->getSpeed();
    }
    if (this->movingRight)
    {
        this->pos.x += this->getSpeed();
    }
}

// Getters And Setters

int Entity::getCurrentHealth()
{
    return this->current_health;
}

int Entity::getMaxHealth()
{
    return this->max_health;
}

Direction Entity::getLookingAt()
{
    return this->looking_at;
}

float Entity::getSpeed()
{
    return this->speed;
}

bool Entity::getIsAlive()
{
    return this->isAlive;
}

void Entity::setMaxHealth(int health)
{
    this->max_health = health;
}

void Entity::setCurrentHealth(int health)
{
    this->current_health = health;
}

void Entity::setLookingAt(Direction direction)
{
    this->looking_at = direction;
}

void Entity::setSpeed(float speed)
{
    this->speed = speed;
}

void Entity::setIsAlive(bool isAlive)
{
    this->isAlive = isAlive;
}

// Movement Functions
void Entity::moveUp()
{
    this->movingUp = true;
}

void Entity::moveDown()
{
    this->movingDown = true;
}

void Entity::moveLeft()
{
    this->movingLeft = true;
}

void Entity::moveRight()
{
    this->movingRight = true;
}

void Entity::stopUp()
{
    this->movingUp = false;
}

void Entity::stopDown()
{
    this->movingDown = false;
}

void Entity::stopLeft()
{
    this->movingLeft = false;
}

void Entity::stopRight()
{
    this->movingRight = false;
}
