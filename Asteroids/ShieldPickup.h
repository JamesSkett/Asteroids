#pragma once
#include "Entity.h"
class ShieldPickup : public Entity
{
public:
	ShieldPickup(GameWorld& world);
	~ShieldPickup();

	void OnCollision(Entity& other) override;
	bool CollidesWith(const Entity& other) const override;


private:

	const int m_shieldPickupValue = 1;

};

