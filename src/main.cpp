#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 720

int main(){
    sf::Window window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Stay So Long", sf::Style::Fullscreen);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, window.getSize().x, window.getSize().y, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);


    while(window.isOpen()){    
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2i(0, 0);
        glVertex2i(100, 0);
        glVertex2i(100, 100);
        glVertex2i(0, 100);
        glEnd();

        window.display();
    }

    return 0;
}