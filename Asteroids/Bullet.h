#pragma once
#include "Entity.h"
class Bullet : public Entity
{
public:

	Bullet(GameWorld& world);

	void Launch(sf::Vector2f startPos, sf::Vector2f direction, Entity* owner);

	const Entity* GetOwner() const { return m_owner ? m_owner : this; }
	float		  GetDamage() const { return m_damage; }

	float GetBulletSpeed() { return m_bulletSpeed; }

	void OnCollision(Entity& other) override;

protected:
	void OnUpdate(float dt) override;
private:

	bool CollidesWith(const Entity& other) const override;

	const float m_bulletSpeed = 1750.0f;

	Entity* m_owner = nullptr;

	float m_damage = 10.0f;
};

