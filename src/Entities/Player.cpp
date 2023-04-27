#include "Player.hpp"

Player::Player(int max_health, int current_health, float speed,
               glm::vec2 pos, glm::vec2 size, sf::Color color) : Entity(max_health, current_health, speed, pos, size, color) {
                    this->desktop = sf::VideoMode::getDesktopMode();
               }
Player::Player() : Entity() {}

void Player::draw()
{
    this->update();
    glPushMatrix();
    glTranslatef(this->pos.x, this->pos.y, 1.0f);
    glScalef(this->size.x, this->size.y, 1.0f);
    glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
    Shapes::Square();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(this->pos.x, this->pos.y + this->size.y / 2, 1.0f);
    glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
    Shapes::Circle(15, 36);
    glPopMatrix();
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
