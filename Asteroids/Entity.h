#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void Update() = 0;
	virtual void Draw() = 0;
protected:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
private:

};

