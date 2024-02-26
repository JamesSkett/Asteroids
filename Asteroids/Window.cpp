#include "Window.h"

Window::Window(uint32_t width, uint32_t height, const sf::String& title)
	: mWindow(sf::VideoMode(width, height), title)
{
	mWindow.setVerticalSyncEnabled(true);
}

bool Window::HandleEvents()
{
	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mWindow.close();
		}
		else if (event.type == sf::Event::Resized)
		{
			sf::Vector2u size = sf::Vector2u(event.size.width, event.size.height);

			mWindow.setSize(size);
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				mWindow.close();
			}
		}
	}

	return mWindow.isOpen();
}

void Window::BeginFrame()
{
	mWindow.clear();
}

void Window::Display()
{
	mWindow.display();
}