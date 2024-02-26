#pragma once
#include "Window.h"

class GameWorld
{
public:
	struct Resources
	{
		sf::Texture mPlayerTex;
		sf::Texture	mAsteroidTex;

		sf::Font mMainFont;
	};

	GameWorld(Window& window);

	bool Load();

	void Update(float dt);
	void Render();

	void Shutdown();
};

