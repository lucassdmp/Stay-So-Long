#include "World.hpp"
#include "../Util/functions.hpp"

World::World(float &dt, sf::RenderWindow &window) : dt(&dt), window(&window)
{
  glm::vec2 initialPlayerPos = glm::vec2(window.getSize().x / 2, window.getSize().y / 2);
  glm::vec2 playerSize = glm::vec2(20.0f, 20.0f);
  player = new Player(100, 100, 10.0f, initialPlayerPos, playerSize, sf::Color::White);

  asteroidTimerMax = 10.0f;
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

    float size = dis(gen) * 20.0f + 30.0f;
    asteroids.push_back(Asteroid(player->getPos(), glm::vec2(size, size)));

    asteroidTimer = 0.0f;
  }

  // update asteroids
  for (auto &asteroid : asteroids)
  {
    asteroid.move();

    for (auto &targetAsteroid: asteroids)
    {
      if (&asteroid != &targetAsteroid)
      {
        if (checkCollision(asteroid, targetAsteroid))
        {
          float distance = glm::distance(asteroid.getPos(), targetAsteroid.getPos());

          glm::vec2 direction = glm::normalize(asteroid.getPos() - targetAsteroid.getPos());

          asteroid.setDirection(direction);
          targetAsteroid.setDirection(-direction);
        }
      }
    }
  }

  // check for collisions
  if (asteroids.size() > 0)
  {
    auto i = std::remove_if(asteroids.begin(), asteroids.end(), [&](Asteroid &asteroid) {
      if (asteroid.getOutOfBoundsTimer() > 1.0f)
        return true;

      if (checkCollision(*player, asteroid) && player->getIsAlive())
      {
        player->takeDamage(10);
        return true;
      }

      return false;
    });

    if (i != asteroids.end())
      asteroids.erase(i);
  }
}

std::vector<Asteroid> World::asteroids;