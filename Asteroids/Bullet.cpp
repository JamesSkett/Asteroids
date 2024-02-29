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
	GetSprite().setOrigin(GetSprite().getLocalBounds().width * Math::Half, GetSprite().getLocalBounds().height * Math::Half);
	SetRadius(5.0f);
}

void Bullet::Launch(sf::Vector2f startPos, sf::Vector2f direction, const Entity* owner)
{
	SetPosition(startPos);
	SetVelocity(Math::Normalised(direction) * sBulletSpeed);

	mOwner = owner;
}

void Bullet::OnCollision(Entity& other)
{
	if (&other != mOwner)
	{
		other.ApplyDamage(this, 1);
		Kill();
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
	return &other != mOwner && ((dynamic_cast<const Asteroid*>(&other) != nullptr) /*|| (dynamic_cast<const Enemy*>(&other) != nullptr)*/);
}
