#pragma once

#include <glm/glm.hpp>
#include "../Util/GameObject.hpp"
#include "../Util/Shapes.hpp"
#include <SFML/OpenGL.hpp>

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Entity : public GameObject
{
private:
    int max_health;
    int current_health;
    Direction looking_at;
    float speed;

protected:
    bool movingUp, movingDown, movingLeft, movingRight, isAlive;

public:
    Entity(int max_health, int current_health, float speed, glm::vec2 pos, glm::vec2 size, sf::Color color);
    Entity();
    void update();

    int getCurrentHealth();
    int getMaxHealth();
    Direction getLookingAt();
    float getSpeed();
    bool getIsAlive();
    void setMaxHealth(int health);
    void setCurrentHealth(int health);
    void setLookingAt(Direction direction);
    void setSpeed(float speed);
    void setIsAlive(bool isAlive);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void stopUp();
    void stopDown();
    void stopLeft();
    void stopRight();

};