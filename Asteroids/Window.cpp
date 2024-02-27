#include "Window.h"

Window::Window(uint32_t width, uint32_t height, const sf::String& title)
	: m_window(sf::VideoMode(width, height), title)
{
	m_window.setVerticalSyncEnabled(true);

}

bool Window::HandleEvents()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		else if (event.type == sf::Event::Resized)
		{
			sf::Vector2u size = sf::Vector2u(event.size.width, event.size.height);

			m_window.setSize(size);
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
			}
		}
	}

	return m_window.isOpen();
}

void Window::BeginFrame()
{
	m_window.clear();
}

void Window::Display()
{
	m_window.display();
}