#include "Asteroid.h"
#include "GameWorld.h"
#include "Ship.h"

Asteroid::Asteroid(GameWorld& world)
	: Entity(world, world.GetResources().m_asteroidTex)
{
	SetMaxLives(1);
	SetCurrentLives(1);
	SetAsteroidSize(e_asteroidSize::LARGE);
	SetCanWrap(false);
	GetSprite().setOrigin(GetSprite().getLocalBounds().width * Math::Half, GetSprite().getLocalBounds().height * Math::Half);

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

}

void Asteroid::OnUpdate(float dt)
{
	m_rotation += (m_rotationSpeed * dt);
	SetRotation(m_rotation);

	m_enableWrapTimer -= dt;
	if (m_enableWrapTimer < 0.0f)
	{
		m_enableWrapTimer += s_enableWrapTime;

		SetCanWrap(true);
	}
}

void Asteroid::OnDestroy()
{
	e_asteroidSize newSize = e_asteroidSize::MEDIUM;
	switch (m_asteroidSize)
	{
	case Asteroid::e_asteroidSize::SMALL:
		return;
	case Asteroid::e_asteroidSize::MEDIUM:
		newSize = e_asteroidSize::SMALL;
		break;
	case Asteroid::e_asteroidSize::LARGE:
		newSize = e_asteroidSize::MEDIUM;
		break;
	default:
		break;
	}
	Asteroid* newAsteroid1 = GetWorld().SpawnEntity<Asteroid>();
	Asteroid* newAsteroid2 = GetWorld().SpawnEntity<Asteroid>();

	newAsteroid1->SetPosition(GetPosition());
	newAsteroid2->SetPosition(GetPosition());
	newAsteroid1->SetAsteroidSize(newSize);
	newAsteroid2->SetAsteroidSize(newSize);
	newAsteroid1->SetCanWrap(true);
	newAsteroid2->SetCanWrap(true);
}

void Asteroid::SetAsteroidSize(e_asteroidSize size)
{
	m_asteroidSize = size;

	switch (m_asteroidSize)
	{
	case Asteroid::e_asteroidSize::SMALL:
		m_scale = 1.0f;
		SetRadius(8.0f);
		break;
	case Asteroid::e_asteroidSize::MEDIUM:
		m_scale = 1.5f;
		SetRadius(16.0f);
		break;
	case Asteroid::e_asteroidSize::LARGE:
		m_scale = 2.0f;
		SetRadius(24.0f);
		break;
	default:
		break;
	}
	GetSprite().setScale(m_scale, m_scale);

	sf::Vector2f vel(Math::FRandRange(-1.0f, 1.0f), Math::FRandRange(-1.0f, 1.0f));
	vel = Math::Normalised(vel);

	const float moveSpeed = Math::Lerp(s_minMoveSpeed, s_maxMoveSpeed, m_scale);
	SetVelocity(vel * moveSpeed);
	SetMaxSpeed(moveSpeed);

	m_rotationSpeed = Math::Lerp(s_minRotationSpeed, s_maxRotationSpeed, m_scale);

	SetMaxLives(1);
	SetCurrentLives(1);
}