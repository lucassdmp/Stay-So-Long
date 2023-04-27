#pragma once

#include <glm/glm.hpp>
#include "../Entities/Entity.hpp"
#include <SFML/OpenGL.hpp>

class Player : public Entity
{
public:
    Player(int max_health, int current_health, float speed, glm::vec2 pos, glm::vec2 size, sf::Color color);
    Player();
    
    void draw();
};