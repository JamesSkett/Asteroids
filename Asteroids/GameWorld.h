#pragma once
#include "Window.h"

class Entity;
class Ship;

class GameWorld
{
public:
	struct Resources
	{
		sf::Texture m_playerTex;
		sf::Texture	m_asteroidTex;

		sf::Font m_MainFont;
	};

	GameWorld(Window& window);

	bool Load();

	void Update(float dt);
	void Draw();

	void Shutdown();

	sf::RenderWindow& GetRenderTex() const { return m_window.GetRenderWindow(); }
	const Resources& GetResources() const { return m_resources; }

	template<typename T>
	T* SpawnEntity();

private:

	Resources m_resources;

	Window& m_window;

	Ship* m_ship = nullptr;
	std::vector<Entity*> m_entities;
	std::vector<Entity*> m_entitiesToAdd;

	void UpdateEntities(float dt);

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