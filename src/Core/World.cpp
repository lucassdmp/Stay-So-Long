#include "World.hpp"
#include "Game.hpp"
#include "../Util/functions.hpp"
#include "../Util/Input.hpp"
#include <sstream>

World::World(float &dt, sf::RenderWindow &window) : dt(&dt), window(&window)
{ 
  glm::vec2 initialPlayerPos = glm::vec2(window.getSize().x / 2, window.getSize().y / 2);
  glm::vec2 playerSize = glm::vec2(20.0f, 20.0f);
  player = new Player(100, 100, 10.0f, initialPlayerPos, playerSize, sf::Color::White);

  asteroidTimerMax = 30.0f;
  asteroidTimer = 0.0f;

  enemyTimerMax = 20.0f;
  enemyTimer = 0.0f;

  timeBetweenWaves = 3.0f;
  waveTimer = 0.0f;
}

World::~World()
{
  delete player;
  delete boss;
  asteroids.clear();
  enemies.clear();
  enemiesToSpawn.clear();
}

void World::Update()
{  
  if (currentWave == bossWaveStep)
  {
    if (boss == nullptr)
    {
      asteroids.clear();
      enemies.clear();
      enemiesToSpawn.clear();
      boss = new Boss(glm::vec2(window->getSize().x / 2, -500.0f), glm::vec2(150.0f, 150.0f), sf::Color::Red);
    }
  }

  if (boss != nullptr)
  {
    boss->fixedUpdate();

    if (!boss->getIsAlive())
    {
      delete boss;
      boss = nullptr;
      currentWave++;
      waveTimer = 0.0f;
      bossWaveStep += 5;
    }
  }
  else
  {
    handleWaves();
    handleAsteroids();
    handleEnemies();
  }

  if (!player->getIsAlive())
  {
    Game::Pause();
    return;
  }

  Game::texts["score"].setString("Score: " + std::to_string(score));

  if (waveTimer > 0.0f)
  {
    std::ostringstream out;
    out.precision(2);
    out << std::fixed << timeBetweenWaves - waveTimer;
    Game::texts["wave"].setString("Next wave in: " + out.str());
  }
  else
  {
    Game::texts["wave"].setString("Wave: " + std::to_string(currentWave));
  }

  player->fixedUpdate(*dt, *window);
}

void World::Render()
{
  if (boss != nullptr)
  {
    boss->draw();

    for (auto &projectile : boss->getProjectiles())
      projectile.draw();
  }

  for (auto &asteroid : asteroids)
    asteroid.draw();

  for (auto &enemy : enemies)
  {
    enemy.draw();

    for (auto &bullet : enemy.getBullets())
      bullet.draw();
  }

  for (auto &projectile : player->getProjectiles())
    projectile.draw();

  player->draw(*dt, *window);
}

void World::restartGame()
{
  delete player;
  delete boss;
  boss = nullptr;
  asteroids.clear();
  enemies.clear();
  enemiesToSpawn.clear();

  glm::vec2 initialPlayerPos = glm::vec2(window->getSize().x / 2, window->getSize().y / 2);
  glm::vec2 playerSize = glm::vec2(20.0f, 20.0f);
  player = new Player(100, 100, 10.0f, initialPlayerPos, playerSize, sf::Color::White);
  player->setVelocity(glm::vec2(0.0f, 0.0f));
  player->setCurrentSpeed(0.0f);

  asteroidTimer = 0.0f;
  enemyTimer = 0.0f;
  waveTimer = 0.0f;

  score = 0;
  currentWave = 0;
}

void World::handleAsteroids()
{  
  // spawn asteroids
  asteroidTimer += 0.1f;
  if (asteroidTimer >= asteroidTimerMax)
  {
    int numAsteroids = genRandomNumberInRange(1, 3);
    for (int i = 0; i < numAsteroids; i++)
    {
      float size = genRandomNumberInRange(30, 50);

      asteroids.push_back(Asteroid(player->getPos(), glm::vec2(size, size)));
    }

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
        score += 10;
        return true;
      }

      return false;
    });

    if (i != asteroids.end())
    {
      asteroids.erase(i);
    }
  }
}

void World::handleEnemies()
{
  for (auto &enemy : enemies)
  {
    enemy.fixedUpdate();

    if (checkCollision(*player, enemy) && player->getIsAlive())
    {
      player->takeDamage(10);
      enemy.takeDamage(10);
    }

    for (auto &targetEnemy : enemies)
    {
      if (&enemy != &targetEnemy)
      {
        if (checkCollision(enemy, targetEnemy))
        {
          float distance = glm::distance(enemy.getPos(), targetEnemy.getPos());

          float overlap = 0.1f * (distance - enemy.getSize().x / 2 - targetEnemy.getSize().x / 2);

          glm::vec2 direction = glm::normalize(enemy.getPos() - targetEnemy.getPos());

          enemy.setPos(overlap * direction + enemy.getPos());
          targetEnemy.setPos(overlap * -direction + targetEnemy.getPos());
        }
      }
    }
  }

  if (enemies.size() > 0)
  {
    auto i = std::remove_if(enemies.begin(), enemies.end(), [&](Enemy &enemy) {
      if (!enemy.getIsAlive() && player->getIsAlive())
        return true;

      return false;
    });

    if (i != enemies.end())
    {
      score += 10;
      enemies.erase(i);
    }
  }
}

void World::handleWaves()
{
  if (enemiesToSpawn.empty() && enemies.empty())
  {
    waveTimer += 1.0f / 60.0f;
    if (waveTimer >= timeBetweenWaves)
    {
      currentWave++;

      int totalEnemies = genRandomNumberInRange(3, 5) * currentWave;

      for (int i = 0; i < totalEnemies; i++)
      {
        enemiesToSpawn.push_back(Enemy(generateRandomPositionOutsideWindow(*window), glm::vec2(40.0f, 40.0f), sf::Color::Red));
      }

      waveTimer = 0.0f;
    }
  }

  if (enemiesToSpawn.size() > 0 && enemies.empty())
  {   
    int totalEnemiesToSpawn = genRandomNumberInRange(1, 3) * currentWave / 2;

    if (totalEnemiesToSpawn > enemiesToSpawn.size())
      totalEnemiesToSpawn = enemiesToSpawn.size();

    for (int i = 0; i < totalEnemiesToSpawn; i++)
    {
      enemies.push_back(enemiesToSpawn.back());
      enemiesToSpawn.pop_back();
    }
  }
}

Player *World::player = nullptr;
Boss *World::boss = nullptr;
std::vector<Asteroid> World::asteroids;
std::vector<Enemy> World::enemies;
int World::score = 0;