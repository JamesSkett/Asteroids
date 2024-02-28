#include "Bullet.h"
#include "Ship.h"
#include "GameWorld.h"

Bullet::Bullet(GameWorld& world)
	: Entity(world, world.GetResources().m_bulletTex)
{
	SetCurrentLives(1);
	SetMaxLives(1);
	GetSprite().setScale(0.3f, 0.3f);
	SetCanWrap(false);
}

void Bullet::Launch(sf::Vector2f startPos, sf::Vector2f direction, const Entity* owner)
{
	//GetSprite().setColor(params.mColor);

	SetPosition(startPos);
	SetVelocity(Math::Normalised(direction) * sBulletSpeed);

	mOwner = owner;
}

void Bullet::OnCollision(Entity& other)
{
	if (&other != mOwner)
	{
		Kill();
	}
}

void Bullet::OnUpdate(float dt)
{

}

bool Bullet::CollidesWith(const Entity& other) const
{
	return &other != mOwner; //&& ((dynamic_cast<const Ship*>(&other) != nullptr) /*|| (dynamic_cast<const Enemy*>(&other) != nullptr)*/);
}
