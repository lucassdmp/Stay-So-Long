#include "GameObject.hpp"
#include <glm/glm.hpp>

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, sf::Color color) :  pos(pos), size(size), color(color){}
GameObject::GameObject(){}

glm::vec2 GameObject::getPos(){
    return this->pos;
}
glm::vec2 GameObject::getSize(){
    return this->size;
}

sf::Color GameObject::getColor(){
    return this->color;
}
void GameObject::setPos(glm::vec2 pos){
    this->pos = pos;
}
void GameObject::setSize(glm::vec2 size){
    this->size = size;
}
void GameObject::setColor(sf::Color color){
    this->color = color;
}

void GameObject::move(glm::vec2 mov){
    this->pos += mov;
}