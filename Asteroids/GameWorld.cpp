#include "GameWorld.h"
#include "Entity.h"
#include "Ship.h"
#include "Asteroid.h"

#include <random>
GameWorld::GameWorld(Window& window)
	: m_window(window)
{
}

bool GameWorld::Load()
{
	bool success = true;

	// Check if assets load correctly
	success &= m_resources.m_shipTex.loadFromFile("./assets/Ship.png");
	success &= m_resources.m_asteroidTex.loadFromFile("./assets/Asteroid.png");
	success &= m_resources.m_bulletTex.loadFromFile("./assets/Bullet.png");

	//success &= m_Resources.m_MainFont.loadFromFile("./assets/Fonts/RussoOne-Regular.ttf");

	m_ship = SpawnEntity<Ship>();

	SpawnNewAsteroid();
	SpawnNewAsteroid();

	// Return result of above statements
	return true;
}

void GameWorld::Update(float dt)
{
	UpdateEntities(dt);
	UpdateAsteroids(dt);
	UpdateCollisions();
}

void GameWorld::Draw()
{
	sf::RenderWindow& rt = m_window.GetRenderWindow();

	for (Entity* entity : m_entities)
	{
		if (entity != nullptr && !entity->IsDead())
		{
			entity->Draw(GetRenderWindow());
		}
	}
}

void GameWorld::Shutdown()
{
	if (m_ship != nullptr)
	{
		delete m_ship;
		m_ship = nullptr;
	}
}

void GameWorld::UpdateEntities(float dt)
{
	for (Entity* entity : m_entitiesToAdd) { m_entities.push_back(entity); }

	m_entitiesToAdd.clear();

	for (Entity* entity : m_entities)
	{
		if (entity != nullptr && !entity->IsDead())
		{
			entity->Update(dt);
		}
	}

	for (auto it = m_entities.begin(); it < m_entities.end();)
	{
		if (Entity* entity = *it)
		{
			if (entity->IsDead())
			{
				entity->Destroy();

				if (entity == m_ship)
				{
					m_ship = nullptr;
				}

				delete entity;
				it = m_entities.erase(it);
			}
			else
			{
				++it;
			}
		}
		else
		{
			it = m_entities.erase(it);
		}
	}
}

void GameWorld::UpdateAsteroids(float dt)
{
	m_asteroidSpawnTimer -= dt;
	if (m_asteroidSpawnTimer < 0.0f)
	{
		m_asteroidSpawnTimer += s_asteroidSpawnTime;

		SpawnNewAsteroid();
	}
}

void GameWorld::SpawnNewAsteroid()
{
	// Determine side to spawn the entity from
	enum class Side { Top, Bottom, Left, Right };
	Side side = static_cast<Side>(Math::IRandRange(0, 3));

	sf::Vector2f spawnPos;
	float buffer = 50.0f;
	switch (side)
	{
	case Side::Top:
		spawnPos = sf::Vector2f(Math::FRandRange(0, m_window.GetRenderWindow().getSize().x - buffer), -buffer);
		break;
	case Side::Bottom:
		spawnPos = sf::Vector2f(Math::FRandRange(0, m_window.GetRenderWindow().getSize().x - buffer), m_window.GetRenderWindow().getSize().y);
		break;
	case Side::Left:
		spawnPos = sf::Vector2f(-buffer, Math::FRandRange(0, m_window.GetRenderWindow().getSize().y - buffer));
		break;
	case Side::Right:
		spawnPos = sf::Vector2f(m_window.GetRenderWindow().getSize().x, Math::FRandRange(0, m_window.GetRenderWindow().getSize().y - buffer));
		break;
	}

	//Check if the spawn pos is within the current view of the screen if not then spawn enemy
	Entity* newAsteroid = SpawnEntity<Asteroid>();
	newAsteroid->SetPosition(spawnPos);
}

void GameWorld::UpdateCollisions()
{
	for (auto it = m_entities.begin(); it < m_entities.end(); ++it)
	{
		for (auto it2 = it + 1; it2 < m_entities.end(); ++it2)
		{
			Entity* a = *it;
			Entity* b = *it2;

			if (a != nullptr && b != nullptr && !a->IsDead() && !b->IsDead())
			{
				if (a->TestCollision(*b))
				{
 					a->OnCollision(*b);
					b->OnCollision(*a);
				}
			}
		}
	}
}