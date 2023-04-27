#include "Player.hpp"

Player::Player(int max_health, int current_health, float speed,
               glm::vec2 pos, glm::vec2 size, sf::Color color) : Entity(max_health, current_health, speed, pos, size, color) {}
Player::Player() : Entity() {}

void Player::draw()
{
    this->update();
    glPushMatrix();
    glTranslatef(this->pos.x, this->pos.y, 1.0f);
    glScalef(this->size.x, this->size.y, 1.0f);
    glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
    Shapes::Square();
    glColor3f(1.0f, 1.0f, 1.0f);
    glPopMatrix();
}
