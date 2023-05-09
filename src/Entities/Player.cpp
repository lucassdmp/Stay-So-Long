#include "Player.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../Util/functions.hpp"
#include <iostream>
#include "../Util/Input.hpp"

Player::Player(int max_health, int current_health, float speed, glm::vec2 pos, glm::vec2 size, sf::Color color) : 
    Entity(max_health, current_health, speed, pos, size, color) {
        this->animationTime = 1.0f;
        this->animationSpeed = 0.01f;
}

Player::Player() : Entity() {}

void Player::fixedUpdate(float dt, sf::RenderWindow &window)
{
    if (Input::get_key(sf::Keyboard::W))
        this->pos.y -= this->getSpeed();
    if (Input::get_key(sf::Keyboard::A))
        this->pos.x -= this->getSpeed();
    if (Input::get_key(sf::Keyboard::S))
        this->pos.y += this->getSpeed();
    if (Input::get_key(sf::Keyboard::D))
        this->pos.x += this->getSpeed();

    this->update();
    this->draw(dt, window);
}

void Player::draw(float dt, sf::RenderWindow &window)
{
    animationTime -= animationSpeed;

    if (animationTime < 0.0f)
    {
        animationTime = 0.5f;
    }
    
    // draw the player's gun first so it's behind the player when looking up
    this->gun.update(this->pos, window, *this);

    // make the player's body wave up and down as they move
    float waveX = wave(this->animationTime, 0.2f, 0.3f, 0.5f);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(this->pos.x, this->pos.y, 0.0f));
    model = glm::scale(model, glm::vec3(this->size.x * waveX + 20.0f, -this->size.y * waveX + 50.0f, 1.0f));
    // body
    glPushMatrix();
    glColor3f(this->color.r, this->color.g, this->color.b);
    glMultMatrixf(&model[0][0]);
    Shapes::Square();
    glPopMatrix();

    // right eye
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    
    if (this->getLookingAt() == Direction::RIGHT)
        glTranslatef(this->pos.x + 10.0f, this->pos.y - 10.0f, 0.0f);
    else if (this->getLookingAt() == Direction::LEFT)
        glTranslatef(this->pos.x - 10.0f, this->pos.y - 10.0f, 0.0f);
    else if (this->getLookingAt() == Direction::DOWN)
        glTranslatef(this->pos.x + 10.0f, this->pos.y - 10.0f, 0.0f);

    glScalef(5.0f, 5.0f, 1.0f);
    Shapes::Square();
    glPopMatrix();

    // left eye, rendered only when looking down
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);

    if (this->getLookingAt() == Direction::DOWN)
        glTranslatef(this->pos.x - 10.0f, this->pos.y - 10.0f, 0.0f);

    glScalef(5.0f, 5.0f, 1.0f);
    Shapes::Square();
    glPopMatrix();
}
