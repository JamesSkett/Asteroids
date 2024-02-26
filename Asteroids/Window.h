#pragma once
#include <SFML/Graphics.hpp>

class Window
{
public:

	Window(uint32_t width, uint32_t height, const sf::String& title);

	// Handles and windows events, returns true if the window is still active
	bool HandleEvents();

	void BeginFrame();

	void Display();

	sf::RenderWindow& GetRenderWindow() { return mWindow; }

private:

	sf::RenderWindow mWindow;
};