#include "ShieldPickup.h"
#include "GameWorld.h"
#include "Ship.h"

ShieldPickup::ShieldPickup(GameWorld& world)
	: Entity(world, world.GetResources().m_shieldTex)
{
	SetRadius(16.0f);
}

ShieldPickup::~ShieldPickup()
{
}

void ShieldPickup::OnCollision(Entity& other)
{
	if (Ship* ship = dynamic_cast<Ship*>(&other))
	{
		ship->AddShield(m_shieldPickupValue);

		Kill();
	}
}

bool ShieldPickup::CollidesWith(const Entity& other) const
{
	return (dynamic_cast<const Ship*>(&other) != nullptr);
}
