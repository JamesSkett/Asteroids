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

	void SetAsteroidSize(e_asteroidSize size);
	e_asteroidSize GetAsteroidSize() { return m_asteroidSize; }
protected:

	void OnUpdate(float dt) override;
	void OnCollision(Entity& other) override;

	// Override to modify any damage being applied.
	void OnApplyDamage(const Entity* source, float& damage) override;

	void OnDestroy() override;
private:
	e_asteroidSize m_asteroidSize = e_asteroidSize::LARGE;

	static constexpr float s_minMoveSpeed = 50.0f;
	static constexpr float s_maxMoveSpeed = 100.0f;
	static constexpr float s_minRotationSpeed = Math::Pi * 0.25f;
	static constexpr float s_maxRotationSpeed = Math::Pi * 0.5f;
	static constexpr float s_enableWrapTime = 0.5f;

	float m_scale = 1.5f;
	float m_rotationSpeed = 0.0f;
	float m_enableWrapTimer = s_enableWrapTime;
};

