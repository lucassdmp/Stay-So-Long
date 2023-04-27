#include "Projectile.hpp"

Projectile::Projectile(glm::vec2 direction, glm::vec2 pos, glm::vec2 size, sf::Color color) : GameObject(pos, size, color){
    this->direction = direction;
}

Projectile::Projectile() : GameObject(){
    this->direction = glm::vec2(0, 0);
}

void Projectile::draw(){
    glPushMatrix();
    glTranslatef(this->pos.x, this->pos.y, 0);
    glColor3f(this->color.r, this->color.g, this->color.b);
    Shapes::Circle(5, 36);
    glPopMatrix();
}

void Projectile::update(){
    this->pos += this->direction;
}