#include "Entity.h"
#include "GameWorld.h"

Entity::Entity(GameWorld& world, const sf::Texture& texture)
	: m_world(world), m_sprite(texture)
{
	m_inGrace = true;
}

Entity::~Entity()
{
}

void Entity::Destroy()
{
	OnDestroy();
}

void Entity::Update(float dt)
{
	m_graceTimer -= dt;
	if (m_graceTimer < 0.0f)
	{
		m_graceTimer += s_graceTime;

		m_inGrace = false;
	}

	// Update velocity based on acceleration and deltaTime
	m_velocity += m_acceleration * dt;

	// clamp speed
	if (Math::LengthSq(m_velocity) > (m_maxSpeed * m_maxSpeed))
	{
		m_velocity = Math::Normalised(m_velocity);
		m_velocity *= m_maxSpeed;
	}

	m_position += m_velocity * dt;

	// Handle the screen wrapping
	if (m_canWrap)
	{
		if (m_position.x + m_sprite.getLocalBounds().width * Math::Half < 0.0f)
			m_position.x = m_world.GetRenderWindow().getSize().x;
		if (m_position.x > m_world.GetRenderWindow().getSize().x)
			m_position.x = -m_sprite.getLocalBounds().width * Math::Half;
		if (m_position.y + m_sprite.getLocalBounds().height * Math::Half < 0.0f)
			m_position.y = m_world.GetRenderWindow().getSize().y;
		if (m_position.y > m_world.GetRenderWindow().getSize().y)
			m_position.y = -m_sprite.getLocalBounds().height * Math::Half;
	}
	else
	{

	}

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
	if (!m_inGrace)
	{
		if (CollidesWith(other) || other.CollidesWith(*this))
		{
			float dx = GetPosition().x - other.GetPosition().x;
			float dy = GetPosition().y - other.GetPosition().y;
			float distance = Math::Length(sf::Vector2f(dx, dy));

			if (distance < GetRadius() + other.GetRadius())
			{
				printf("Collision");
				return true;
			}
		}
	}

	return false;
}

void Entity::ApplyDamage(const Entity* source, float damage)
{
	OnApplyDamage(source, damage);

	m_currentLives -= damage;
}