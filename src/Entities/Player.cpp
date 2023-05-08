#include "Player.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../Util/functions.hpp"
#include <iostream>

Player::Player(int max_health, int current_health, float speed, glm::vec2 pos, glm::vec2 size, sf::Color color) : 
    Entity(max_health, current_health, speed, pos, size, color) {
        this->desktop = sf::VideoMode::getDesktopMode();
        this->animationTime = 1.0f;
        this->animationSpeed = 0.01f;
}

Player::Player() : Entity() {}

void Player::draw(float dt, sf::RenderWindow &window)
{
    this->update();

    animationTime -= animationSpeed;

    if (animationTime < 0.0f)
    {
        animationTime = 0.5f;
    }

    float waveX = wave(this->animationTime, 0.2f, 0.3f, 0.5f);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(this->pos.x, this->pos.y, 0.0f));
    model = glm::scale(model, glm::vec3(this->size.x * waveX + 30.0f, -this->size.y * waveX + 70.0f, 1.0f));

    glPushMatrix();
    glColor3f(this->color.r, this->color.g, this->color.b);
    glMultMatrixf(&model[0][0]);
    Shapes::Square();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    
    if (this->getLookingAt() == Direction::RIGHT)
        glTranslatef(this->pos.x + 20.0f, this->pos.y - 25.0f, 0.0f);
    else if (this->getLookingAt() == Direction::LEFT)
        glTranslatef(this->pos.x - 20.0f, this->pos.y - 25.0f, 0.0f);
    else if (this->getLookingAt() == Direction::DOWN)
        glTranslatef(this->pos.x + 13.0f, this->pos.y - 25.0f, 0.0f);

    glScalef(5.0f, 5.0f, 1.0f);
    Shapes::Square();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);

    if (this->getLookingAt() == Direction::DOWN)
        glTranslatef(this->pos.x - 13.0f, this->pos.y - 25.0f, 0.0f);

    glScalef(5.0f, 5.0f, 1.0f);
    Shapes::Square();
    glPopMatrix();

    gun.update(this->pos, window);
    gun.draw();
}

void Player::attack()
{
    glPopMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);

    if (this->getLookingAt() == Direction::UP)
    {
        this->projectiles.push_back(Projectile(glm::vec2(0, 5), glm::vec2(this->pos.x + this->size.x / 2, this->pos.y), glm::vec2(10, 10), sf::Color::White));
    }
    else if (this->getLookingAt() == Direction::DOWN)
    {
        this->projectiles.push_back(Projectile(glm::vec2(0, -5), glm::vec2(this->pos.x + this->size.x / 2, this->pos.y + this->size.y), glm::vec2(10, 10), sf::Color::White));
    }
    else if (this->getLookingAt() == Direction::LEFT)
    {
        this->projectiles.push_back(Projectile(glm::vec2(-5, 0), glm::vec2(this->pos.x, this->pos.y + this->size.y / 2), glm::vec2(10, 10), sf::Color::White));
    }
    else if (this->getLookingAt() == Direction::RIGHT)
    {
        this->projectiles.push_back(Projectile(glm::vec2(5, 0), glm::vec2(this->pos.x + this->size.x, this->pos.y + this->size.y / 2), glm::vec2(10, 10), sf::Color::White));
    }
    glPushMatrix();
}

void Player::updateAttacks()
{
    for (int i = 0; i < this->projectiles.size(); i++)
    {
        this->projectiles[i].update();
        if(this->projectiles[i].getPos().x < 0 || this->projectiles[i].getPos().x > desktop.width || this->projectiles[i].getPos().y < 0 || this->projectiles[i].getPos().y > desktop.height)
            this->projectiles.erase(this->projectiles.begin() + i);
        this->projectiles[i].draw();
    }
}
