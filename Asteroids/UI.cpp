#include "UI.h"
#include "GameWorld.h"
#include "Ship.h"

UI::UI(const GameWorld& world)
	: m_World(world)
{
}

void UI::Render(sf::RenderWindow& rw)
{
	RenderPlayerStats(rw);
}

void UI::RenderPlayerStats(sf::RenderWindow& rw)
{
	sf::Text text;
	text.setFont(m_World.GetResources().m_mainFont);
	text.setCharacterSize(24);
	text.setStyle(sf::Text::Bold);

	const Ship* ship = m_World.GetShip();

	if (ship != nullptr)
	{
		std::string outputStr = "Lives: " + std::to_string(ship->GetCurrentLives());

		text.setString(outputStr);
		text.setPosition(10.0f, 10.0f);
		rw.draw(text);

		outputStr = "Score: " + std::to_string(ship->GetCurrentScore());

		text.setString(outputStr);
		text.setPosition(rw.getSize().x - 150, 10);
		rw.draw(text);
	}
	else
	{
		text.setString("Game Over");
		text.setPosition(rw.getSize().x / 2 - (text.getLocalBounds().width / 2), rw.getSize().y / 2);
		rw.draw(text);

		text.setString("High Score: " + std::to_string(m_World.GetFinalScore()));
		text.setPosition(rw.getSize().x / 2 - (text.getLocalBounds().width / 2), rw.getSize().y / 2 + 50);
		rw.draw(text);
	}
}
