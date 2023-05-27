#pragma once

#include <glm/glm.hpp>
#include "../Entities/Entity.hpp"
#include <SFML/OpenGL.hpp>
#include "Projectile.hpp"
#include <vector>
#include <SFML/Window.hpp>

class Player : public Entity
{
public:
    Player();
    Player(int max_health, int current_health, float speed, glm::vec2 pos, glm::vec2 size, sf::Color color);

    void fixedUpdate(float dt, sf::RenderWindow &window);
    void draw(float dt, sf::RenderWindow &window);
    void drawCrosshair();
    void drawHealthBar();
    void shoot();
    void handleShots(sf::RenderWindow &window);
    void move(float dt);
    void checkBounds(sf::RenderWindow &window);
    void handleUpgrades();

    std::vector<Projectile> getProjectiles() { return projectiles; }

    void setLevel(int level) { this->current_level = level; }
    int getLevel() { return this->current_level; }

    void setCurrentSpeed(float speed) { this->current_speed = speed; }
    void setVelocity(glm::vec2 velocity) { this->velocity = velocity; }

private:
    float angle = 0.0f;
    float shot_cooldown = 2.0f;
    float shot_timer = 0.0f;
    glm::vec2 lookDir;
    std::vector<Projectile> projectiles;
    
    float max_speed = 300.0f;
    float acceleration = 10.0f;
    float deceleration = 1.0f;
    float current_speed = 0.0f;
    glm::vec2 velocity;

    int current_level = 1;
    int max_level = 3;
    int level_up_score_step = 50;
};