#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 720

int main(){
    sf::Window window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Stay So Long", sf::Style::Fullscreen);

    while(window.isOpen()){
        //glBegin();


        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }
    }

    return 0;
}