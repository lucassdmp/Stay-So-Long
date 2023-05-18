#include "World.hpp"
#include "../Util/functions.hpp"

World::World(float &dt, sf::RenderWindow &window) : dt(&dt), window(&window)
{
  player = new Player(100, 100, 10.0f, glm::vec2(window.getSize().x / 2, window.getSize().y / 2), glm::vec2(20.0f, 20.0f), sf::Color::White);

  asteroidTimerMax = 20.0f;
  asteroidTimer = 0.0f;
}

World::~World()
{
  delete player;
  asteroids.clear();
}

void World::Update()
{
  handleAsteroids();
  player->fixedUpdate(*dt, *window);
}

void World::handleAsteroids()
{  
  // spawn asteroids
  asteroidTimer += 0.1f;
  if (asteroidTimer >= asteroidTimerMax)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0f, 1.0f);

    int numAsteroids = std::round(dis(gen)) * 3 + 1;
    for (int i = 0; i < 1; i++)
      asteroids.push_back(Asteroid(player->getPos(), glm::vec2(50.0f, 50.0f)));

    asteroidTimer = 0.0f;
  }

  // update asteroids
  int sizeAsteroid = asteroids.size();
  for (unsigned int i = 0; i < sizeAsteroid; i++)
  {

    if (asteroids[i].getOutOfBoundsTimer() > 1.0f)
    {
      asteroids.erase(asteroids.begin() + i);
      sizeAsteroid--;
      continue;
    }
    else
    {
      asteroids[i].move();
    }
    

    for(unsigned int j = 0; j < this->player->getProjectiles().size(); j++){
        if(checkCollision(asteroids[i], player->getProjectiles()[j])){
            this->player->getProjectiles().erase(this->player->getProjectiles().begin() + j);
            asteroids.erase(asteroids.begin() + i);
            sizeAsteroid--;
            continue;
        }
    }
  }
}