#include "Bullet.h"
#include "Ship.h"
#include "GameWorld.h"
#include "Asteroid.h"

Bullet::Bullet(GameWorld& world)
	: Entity(world, world.GetResources().m_bulletTex)
{
	SetCurrentLives(1);
	SetMaxLives(1);
	GetSprite().setScale(0.3f, 0.3f);
	SetCanWrap(false);
	SetRadius(5.0f);
}

void Bullet::Launch(sf::Vector2f startPos, sf::Vector2f direction, Entity* owner)
{
	SetPosition(startPos);
	SetVelocity(Math::Normalised(direction) * m_bulletSpeed);

	m_owner = owner;
}

void Bullet::OnCollision(Entity& other)
{
	if (&other != m_owner)
	{
		other.ApplyDamage(this, 1);
		Kill();
		if (Ship* ship = dynamic_cast<Ship*>(m_owner))
		{
			ship->UpdateScore(50);
		}
	}
}

void Bullet::OnUpdate(float dt)
{
	if (GetPosition().x + GetSprite().getLocalBounds().width * Math::Half < 0.0f)
		Kill();
	if (GetPosition().x > GetWorld().GetRenderWindow().getSize().x)
		Kill();
	if (GetPosition().y + GetSprite().getLocalBounds().height * Math::Half < 0.0f)
		Kill();
	if (GetPosition().y > GetWorld().GetRenderWindow().getSize().y)
		Kill();
}

bool Bullet::CollidesWith(const Entity& other) const
{
	//Make sure the bullet does not collide with owner
	return &other != m_owner && ((dynamic_cast<const Asteroid*>(&other) != nullptr) /*|| (dynamic_cast<const Enemy*>(&other) != nullptr)*/);
}
