#pragma once
#include "SFML/Graphics.hpp"

class GameWorld;

class UI
{
public:

	UI(const GameWorld& world);

	void Render(sf::RenderWindow& rw);

private:

	const GameWorld& m_World;

	void RenderPlayerStats(sf::RenderWindow& rw);

};

