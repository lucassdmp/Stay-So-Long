#include "Projectile.hpp"
#include <iostream>

Projectile::Projectile(glm::vec2 direction, glm::vec2 pos, glm::vec2 size, sf::Color color) : GameObject(pos, size, color){
    this->direction = direction;
}

Projectile::Projectile() : GameObject(){
    this->direction = glm::vec2(0, 0);
}

Projectile::~Projectile(){
}

void Projectile::draw(){
    glColor3f(this->color.r, this->color.g, this->color.b);
    glPushMatrix();
    glTranslatef(this->pos.x, this->pos.y, 0);
    glScalef(this->size.x / 2, this->size.y / 2, 1.0f);
    Shapes::Circle(1, 36);
    glPopMatrix();
}

void Projectile::update(){
    draw();

    this->move(this->direction);
}