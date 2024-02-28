#include "Asteroid.h"
#include "GameWorld.h"
#include "Ship.h"

Asteroid::Asteroid(GameWorld& world)
	: Entity(world, world.GetResources().m_asteroidTex)
{
	//Set random size
	//set random velocity
}

void Asteroid::OnCollision(Entity& other)
{
	if (Ship* ship = dynamic_cast<Ship*>(&other))
	{
		ship->ApplyDamage(this, 1);
	}
}

void Asteroid::OnApplyDamage(const Entity* source, float& damage)
{
	//spawn 2 new asteroids
	//set correct size
	//set random velocity
	//kill current asteroid
}