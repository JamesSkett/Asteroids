#pragma once
#include "Entity.h"



class Asteroid : public Entity
{
public:
	enum class e_asteroidSize
	{
		SMALL,
		MEDIUM,
		LARGE
	};

	Asteroid(GameWorld& world);

	void OnCollision(Entity& other);

protected:

	// Override to modify any damage being applied.
	void OnApplyDamage(const Entity* source, float& damage) override;

private:
	e_asteroidSize m_asteroidSize = e_asteroidSize::LARGE;
};

