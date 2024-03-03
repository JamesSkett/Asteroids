#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

class GameWorld;

class Entity
{
public:
	Entity(GameWorld& world, const sf::Texture& texture);
	virtual ~Entity();

	void Destroy();

	void Update(float dt);
	void Draw(sf::RenderWindow& rw);

	void				SetAcceleration(const sf::Vector2f& accel) { m_acceleration = accel; }
	const sf::Vector2f& GetAcceleration() const { return m_acceleration; }

	void				SetVelocity(const sf::Vector2f& vel) { m_velocity = vel; }
	const sf::Vector2f& GetVelocity() const { return m_velocity; }

	void				SetPosition(const sf::Vector2f& pos) { m_position = pos; }
	const sf::Vector2f& GetPosition() const { return m_position; }

	void  SetMaxSpeed(float speed) { m_maxSpeed = speed; }
	float GetMaxSpeed() const { return m_maxSpeed; }

	void  SetRotation(float angleRads) { m_sprite.setRotation(Math::RadiansToDegrees(angleRads)); }
	float GetRotation() const { return Math::DegreesToRadians(m_sprite.getRotation()); }

	GameWorld& GetWorld() const { return m_world; }

	sf::Sprite& GetSprite() { return m_sprite; }
	const sf::Sprite& GetSprite() const { return m_sprite; }

	void  SetMaxLives(int lives) { m_maxLives = lives; }
	int GetMaxLives() const { return m_maxLives; }

	void  SetCurrentLives(int lives) { m_currentLives = lives; }
	int GetCurrentLives() const { return m_currentLives; }

	void SetCanWrap(bool canWrap) { m_canWrap = canWrap; }
	bool GetCanWrap() const { return m_canWrap; }

	void SetInGrace(bool inGrace) { m_inGrace = inGrace; }
	bool GetInGrace() const { return m_inGrace; }

	void SetRadius(float radius) { m_radius = radius; }
	float GetRadius() const { return m_radius; }

	void SetGraceTime(float time) { m_graceTimer = time; }
	float GetGraceTime() { return m_graceTimer; }

	void Kill() { m_currentLives = 0; }
	bool IsDead() { return m_currentLives == 0; }

	bool		 TestCollision(const Entity& other);

	void ApplyDamage(const Entity* source, float damage);

	virtual void OnCollision(Entity& other) { }
protected:
	// OVerride to control if this entity can collide with the other.
	virtual bool CollidesWith(const Entity& other) const { return false; }

	// Override to modify any damage being applied.
	virtual void OnApplyDamage(const Entity* source, float& damage) { }

	// Override to respond to this entity being killed.
	virtual void OnDestroy() { }

	// Override to implement update or render functionality for this entity.
	virtual void OnUpdate(float dt) { }
	virtual void OnDraw(sf::RenderWindow& rw) { }

	float m_rotation = 0.0f;

private:
	float m_graceTime = 3.0f;

	GameWorld& m_world;

	sf::Sprite m_sprite;
	sf::Image  m_img;

	sf::Vector2f m_acceleration = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f m_velocity = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f m_position = sf::Vector2f(0.0f, 0.0f);

	float m_maxSpeed = 500.0f;
	float m_graceTimer = m_graceTime;

	int m_maxLives = 3;
	int m_currentLives = 3;

	bool m_canWrap = true;
	bool m_inGrace = false;

	float m_radius = 24.0f;

};

