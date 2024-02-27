#include "Entity.h"

Entity::Entity(GameWorld& world, const sf::Texture& texture)
	: m_world(world), m_sprite(texture)
{
}

Entity::~Entity()
{
}

void Entity::Destroy()
{
}

void Entity::Update(float dt)
{
	// Update velocity based on acceleration and deltaTime
	m_velocity += m_acceleration * dt;

	// clamp speed
	if (Math::LengthSq(m_velocity) > (m_maxSpeed * m_maxSpeed))
	{
		m_velocity = Math::Normalised(m_velocity);
		m_velocity *= m_maxSpeed;
	}

	m_position += m_velocity * dt;

	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_rotation);
	OnUpdate(dt);
}

void Entity::Draw(sf::RenderWindow& rt)
{
	rt.draw(m_sprite);
}

bool Entity::TestCollision(const Entity& other)
{
	return false;
}
