#pragma once
#include "Window.h"
#include "UI.h"

class Entity;
class Ship;

class GameWorld
{
public:
	struct Resources
	{
		sf::Texture m_shipTex;
		sf::Texture	m_asteroidTex;
		sf::Texture m_bulletTex;
		sf::Texture m_shieldTex;

		sf::Font m_mainFont;
	};

	GameWorld(Window& window);

	bool Load();

	void Update(float dt);
	void Draw();

	void Shutdown();

	sf::RenderWindow& GetRenderWindow() const { return m_window.GetRenderWindow(); }
	const Resources& GetResources() const { return m_resources; }
	const Ship* GetShip() const { return m_ship; }

	void SetFinalScore(int score) { m_finalScoreCount = score; }
	int GetFinalScore() const { return m_finalScoreCount; }

	template<typename T>
	T* SpawnEntity();

private:
	const float m_asteroidSpawnTime = 8.0f;
	const float m_pickupSpawnTime = 20.0f;

	Resources m_resources;

	Window& m_window;

	Ship* m_ship = nullptr;
	std::vector<Entity*> m_entities;
	std::vector<Entity*> m_entitiesToAdd;

	UI m_UI;

	float m_asteroidSpawnTimer = m_asteroidSpawnTime;
	float m_spawnPickupTimer = m_pickupSpawnTime;

	int m_finalScoreCount = 0;

	void UpdateEntities(float dt);
	void UpdateAsteroids(float dt);

	void SpawnNewAsteroid();
	void UpdatePickups(float dt);
	void UpdateCollisions();
};

template<typename T>
T* GameWorld::SpawnEntity()
{
	if (T* newEntity = new T(*this))
	{
		m_entitiesToAdd.push_back(newEntity);

		return newEntity;
	}

	return nullptr;
}