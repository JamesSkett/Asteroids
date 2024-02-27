#include "UI.h"
#include "GameWorld.h"

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
	const sf::Vector2f& vpSize = rw.getView().getSize();

	sf::Text text;
	text.setFont(m_World.GetResources().m_MainFont);
	text.setCharacterSize(32);
	text.setStyle(sf::Text::Bold);


}
