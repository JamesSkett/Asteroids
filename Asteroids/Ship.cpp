#include "Ship.h"
#include "GameWorld.h"
#include "Bullet.h"
Ship::Ship(GameWorld& world) 
	: Entity(world, world.GetResources().m_shipTex)
{
	SetPosition(sf::Vector2f(400, 400));
	GetSprite().setOrigin(GetSprite().getLocalBounds().width * Math::Half, GetSprite().getLocalBounds().height * Math::Half);
	SetRadius(32.0f);
}

Ship::~Ship()
{
}

void Ship::UpdateScore(int val)
{
	m_currentScore += val;
}

void Ship::OnUpdate(float dt)
{
	UpdateMovement(dt);
	UpdateGun(dt);

}

void Ship::OnRender(sf::RenderTexture& rt)
{
}

void Ship::OnApplyDamage(const Entity* source, float& damage)
{
	//ship disappear
	//wait a second
	//respawn ship in centre
	//wait 3 seconds until damage can be taken again
}

void Ship::OnDestroy()
{
}

void Ship::UpdateMovement(float dt)
{
	sf::Vector2f accel(0.0f, 0.0f);

	// Calculate thrust with possible adjustments based on SFML coordinate system
	sf::Vector2f thrustDirection = sf::Vector2f(sin(Math::DegreesToRadians(m_rotation)), -cos(Math::DegreesToRadians(m_rotation)));
	accel = (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ? thrustDirection * s_accelerationSpeed : sf::Vector2f(0.f, 0.f);
	


	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	//{
	//	accel.y += 1.0f;
	//}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_rotation += 100.0f * dt;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_rotation -= 100.0f * dt;
	}

	if (Math::LengthSq(accel) > 0.0f)
	{
		accel = Math::Normalised(accel);
		accel *= s_accelerationSpeed;

		SetAcceleration(accel);
	}
	else
	{
		// Slow the player down by reversing velocity
		SetAcceleration(GetVelocity() * -1.0f);
	}
}

void Ship::UpdateGun(float dt)
{
	sf::Vector2f gunDir = sf::Vector2f(sin(Math::DegreesToRadians(m_rotation)), -cos(Math::DegreesToRadians(m_rotation)));


	m_shootCooldown -= dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (m_shootCooldown <= 0.0f)
		{
			m_shootCooldown = s_shootDelay;

			if (Bullet* bullet = GetWorld().SpawnEntity<Bullet>())
			{
				bullet->Launch(GetPosition(), gunDir, this);
			}
		}
	}


}

