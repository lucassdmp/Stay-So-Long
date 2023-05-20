#pragma once

#include <glm/glm.hpp>
#include "../Util/GameObject.hpp"
#include "../Util/Shapes.hpp"
#include <SFML/OpenGL.hpp>

class Entity : public GameObject
{
private:
    int max_health;
    int current_health;
    float speed;
    bool isAlive;

public:
    Entity(int max_health, int current_health, float speed, glm::vec2 pos, glm::vec2 size, sf::Color color);
    Entity();
    void update();
    void takeDamage(int damage) { this->current_health -= damage; }

    int getCurrentHealth() { return this->current_health; }
    int getMaxHealth() { return this->max_health; }
    float getSpeed() { return this->speed; }
    bool getIsAlive() { return this->isAlive; }
    void setMaxHealth(int health) { this->max_health = health;}
    void setCurrentHealth(int health) { this->current_health = health;}
    void setSpeed(float speed) { this->speed = speed;}
    void setIsAlive(bool isAlive) { this->isAlive = isAlive;}
};