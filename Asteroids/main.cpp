#include <SFML/Graphics.hpp>
#include "Window.h"
#include "GameWorld.h"

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	Window	  window(800, 800, "Asteroids");
	GameWorld world(window);

	if (world.Load())
	{
		sf::Clock clock;
		
		while (window.HandleEvents())
		{
			sf::Time frameTime = clock.getElapsedTime();
			clock.restart();

			window.BeginFrame();

			world.Update(frameTime.asSeconds());
			world.Draw();

			window.Display();
		}
	}

	world.Shutdown();

    return 0;
}