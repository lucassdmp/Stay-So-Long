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

    void draw(float dt, sf::RenderWindow &window);
    void attack();
    void updateAttacks();

private:
    int projectileN = 0;
    float animationTime;
    float animationSpeed;
    std::vector<Projectile> projectiles;
    sf::VideoMode desktop;

    Gun gun;
};