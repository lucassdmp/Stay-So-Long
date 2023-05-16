#pragma once

#include <glm/glm.hpp>
#include "../Entities/Entity.hpp"
#include <SFML/OpenGL.hpp>
#include "Projectile.hpp"
#include "Gun.hpp"
#include <vector>
#include <SFML/Window.hpp>

class Player : public Entity
{
public:
    Player();
    Player(int max_health, int current_health, float speed, glm::vec2 pos, glm::vec2 size, sf::Color color);

    void fixedUpdate(float dt, sf::RenderWindow &window);
    void draw(float dt, sf::RenderWindow &window);
    void shoot();
    void handleShots(sf::RenderWindow &window);
    void move();

private:
    float angle = 0.0f;
    float shot_cooldown = 2.0f;
    float shot_timer = 0.0f;
    std::vector<Projectile> projectiles;

    float acceleration = 10.0f;
    float deceleration = 5.0f;
    float current_speed = 0.0f;
    glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
};