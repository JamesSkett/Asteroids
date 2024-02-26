#include "Window.h"

Window::Window(uint32_t width, uint32_t height, const sf::String& title)
	: mWindow(sf::VideoMode(width, height), title)
{
	mWindow.setVerticalSyncEnabled(true);

	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f((float)width, (float)height));
	mWindow.setView(view);

	mRenderTex.create(width, height);
	mRenderTex.setView(view);
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

			sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f((float)size.x, (float)size.y));
			mWindow.setView(view);

			mRenderTex.create(size.x, size.y);
			mRenderTex.setView(view);
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
	mRenderTex.clear();
}

void Window::Display()
{
	mWindow.display();
}