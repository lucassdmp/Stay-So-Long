#pragma once

#include <glm/glm.hpp>
#include "../Util/GameObject.hpp"
#include "../Util/Shapes.hpp"
#include <SFML/OpenGL.hpp>

enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player : public GameObject{
    private:
        int max_health;
        int current_health;
        Direction looking_at;
        float speed;
        bool ismovingup;
    public:
        Player();
        Player(int max_health, int current_health, float speed, glm::vec2 pos, glm::vec2 size, sf::Color color);
        int getCurrentHealth();
        int getMaxHealth();
        Direction getLookingAt();
        float getSpeed();
        void setMaxHealth(int health);
        void setCurrentHealth(int health);
        void setLookingAt(Direction direction);
        void setSpeed(float speed);
        void draw();
        void update();
};