#pragma once
#include "Entity.h"
class Ship : public Entity
{
public:
	Ship(GameWorld& world);
	~Ship();

	int	  GetCurrentScore() const { return m_currentScore; }
	int   GetShieldHealth() const { return m_currentShieldHealth; }
	void  UpdateScore(int val);
	void  AddShield(int val);

	bool GetShieldActive() const { return m_shieldActive; }
protected:
	void OnUpdate(float dt) override;
	void OnDraw(sf::RenderWindow& rw) override;

	void OnApplyDamage(const Entity* source, float& damage) override;

	void OnDestroy() override;

private:
	// Movement

	const float m_accelerationSpeed = 500.0f;
	const float m_maxSpeed = 100.0f;

	// Gun
	const float m_shootDelay = 0.5f;
	float m_shootCooldown = 0.0f;

	//Respawn
	int m_alphaDirection = -1;
	const int m_minAlpha = 50;
	const int m_alphaChangeSpeed = 200;
	sf::Uint8 m_currentAlpha = 255;

	// Score
	int m_currentScore = 0;

	// Shield
	const int m_maxShieldHealth = 3;
	int m_currentShieldHealth = 0;
	bool m_shieldActive = false;

	void UpdateMovement(float dt);
	void UpdateGun(float dt);
	void UpdateShield();

	void DrawShield(sf::RenderWindow& rw);
};

