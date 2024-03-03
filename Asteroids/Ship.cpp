#include "Ship.h"
#include "GameWorld.h"
#include "Bullet.h"
Ship::Ship(GameWorld& world) 
	: Entity(world, world.GetResources().m_shipTex)
{
	SetPosition(sf::Vector2f(400, 400));
	SetRadius(16.0f);
}

Ship::~Ship()
{
}

void Ship::UpdateScore(int val)
{
	m_currentScore += val;
}

void Ship::AddShield(int val)
{
	m_currentShieldHealth += val;

	if (m_currentShieldHealth == m_maxShieldHealth)
	{
		m_currentShieldHealth = m_maxShieldHealth;
	}
}

void Ship::OnUpdate(float dt)
{
	if (GetInGrace())
	{
		m_currentAlpha += m_alphaDirection * m_alphaChangeSpeed * dt;

		if (m_currentAlpha < m_minAlpha)
		{
			m_currentAlpha = m_minAlpha;
			m_alphaDirection = 1;
		}
		else if (m_currentAlpha >= 255)
		{
			m_currentAlpha = 255;
			m_alphaDirection = -1;
		}

	}
	else m_currentAlpha = 255;


	UpdateMovement(dt);
	UpdateGun(dt);
	UpdateShield();
	GetSprite().setColor(sf::Color(255, 255, 255, m_currentAlpha));
}

void Ship::OnDraw(sf::RenderWindow& rw)
{
	DrawShield(rw);
}

void Ship::OnApplyDamage(const Entity* source, float& damage)
{
	if (m_shieldActive)
	{
		m_currentShieldHealth -= damage;
		damage = 0;
		SetInGrace(true);
		SetGraceTime(1.5f);
	}
	else
	{
		//Reset Velocity
		SetVelocity(sf::Vector2f(0.0f, 0.0f));
		SetAcceleration(sf::Vector2f(0.0f, 0.0f));
		//respawn ship in centre
		SetPosition(sf::Vector2f(GetWorld().GetRenderWindow().getSize().x / 2, GetWorld().GetRenderWindow().getSize().y / 2));

		SetInGrace(true);
		SetGraceTime(3.0f);
	}
}

void Ship::OnDestroy()
{
	GetWorld().SetFinalScore(m_currentScore);
}

void Ship::UpdateMovement(float dt)
{
	sf::Vector2f accel(0.0f, 0.0f);

	// Calculate thrust and direction with possible adjustments
	sf::Vector2f thrustDirection = sf::Vector2f(sin(Math::DegreesToRadians(m_rotation)), -cos(Math::DegreesToRadians(m_rotation)));
	accel = (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ? thrustDirection * m_accelerationSpeed : sf::Vector2f(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_rotation += 200.0f * dt;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_rotation -= 200.0f * dt;
	}

	if (Math::LengthSq(accel) > 0.0f)
	{
		accel = Math::Normalised(accel);
		accel *= m_accelerationSpeed;

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
			m_shootCooldown = m_shootDelay;

			if (Bullet* bullet = GetWorld().SpawnEntity<Bullet>())
			{
				bullet->Launch(GetPosition(), gunDir, this);
			}
		}
	}


}

void Ship::UpdateShield()
{
	if (m_currentShieldHealth > 0) 
		m_shieldActive = true;
	else 
		m_shieldActive = false;

}

void Ship::DrawShield(sf::RenderWindow& rw)
{
	if (m_shieldActive)
	{
		sf::CircleShape shield(24.f);

		shield.setPosition(GetPosition().x - shield.getRadius(), GetPosition().y - shield.getRadius());

		shield.setFillColor(sf::Color(0, 0, 255, 100));

		rw.draw(shield);
	}
}

