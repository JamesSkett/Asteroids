#include "GameWorld.h"
#include "Entity.h"
#include "Ship.h"

GameWorld::GameWorld(Window& window)
    : m_window(window)
{
}

bool GameWorld::Load()
{
    bool success = true;

    // Check if assets load correctly
    success &= m_resources.m_playerTex.loadFromFile("./assets/Ship.png");
    success &= m_resources.m_asteroidTex.loadFromFile("./assets/Asteroid.png");

    //success &= m_Resources.m_MainFont.loadFromFile("./assets/Fonts/RussoOne-Regular.ttf");

    m_ship = SpawnEntity<Ship>();

    // Return result of above statements
    return true;
}

void GameWorld::Update(float dt)
{
	UpdateEntities(dt);
}

void GameWorld::Draw()
{
    sf::RenderWindow& rt = m_window.GetRenderWindow();

    for (Entity* entity : m_entities)
    {
        if (entity != nullptr && !entity->IsDead())
        {
            entity->Draw(GetRenderTex());
        }
    }

	//sf::Sprite fullScreenSprite(GetRenderTex().getTexture());

	//const sf::Vector2f& vpSize = m_window.GetRenderWindow().getView().getSize();
	//fullScreenSprite.setOrigin(static_cast<float>(vpSize.x) * Math::Half, static_cast<float>(vpSize.y) * Math::Half);

	//fullScreenSprite.setScale(sf::Vector2f(1.0f, -1.0f));

	//m_window.GetRenderWindow().draw(fullScreenSprite);
}

void GameWorld::Shutdown()
{
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