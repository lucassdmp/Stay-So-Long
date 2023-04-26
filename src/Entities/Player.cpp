#include "Player.hpp"

Player::Player(int max_health, int current_health, float speed, glm::vec2 pos,
 glm::vec2 size, sf::Color color) : GameObject(pos, size, color), looking_at(DOWN), speed(speed){
    this->ismovingup = false;
 }
Player::Player(){};
int Player::getCurrentHealth(){
    return this->current_health;
}

int Player::getMaxHealth(){
    return this->max_health;
}

Direction Player::getLookingAt(){
    return this->looking_at;
}

float Player::getSpeed(){
    return this->speed;
}

void Player::setMaxHealth(int health){
    this->max_health = health;
}

void Player::setCurrentHealth(int health){
    this->current_health = health;
}

void Player::setLookingAt(Direction direction){
    this->looking_at = direction;
}

void Player::setSpeed(float speed){
    this->speed = speed;
}

void Player::draw(){
    glPushMatrix();
    glTranslatef(this->pos.x, this->pos.y, 1.0f);
    glScalef(this->size.x, this->size.y, 1.0f);
    Shapes::Square();
    glPopMatrix();
}

