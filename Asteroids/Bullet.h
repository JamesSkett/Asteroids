#pragma once
#include "Entity.h"
class Bullet : public Entity
{
public:

	Bullet(GameWorld& world);

	void Launch(sf::Vector2f startPos, sf::Vector2f direction, const Entity* owner);

	const Entity* GetOwner() const { return mOwner ? mOwner : this; }
	float		  GetDamage() const { return mDamage; }

	static float GetBulletSpeed() { return sBulletSpeed; }

	void OnCollision(Entity& other) override;

protected:
	void OnUpdate(float dt) override;
private:

	bool CollidesWith(const Entity& other) const override;

	static constexpr float sBulletSpeed = 1750.0f;

	const Entity* mOwner = nullptr;

	float mDamage = 10.0f;
};

