#pragma once
#include "Entity.h"
class Ship : public Entity
{
public:
	Ship(GameWorld& world);
	~Ship();

	int	  GetCurrentScore() const { return m_currentScore; }
	void  UpdateScore(int val);

protected:
	void OnUpdate(float dt) override;
	void OnRender(sf::RenderTexture& rt) override;

	void OnApplyDamage(const Entity* source, float& damage) override;

	void OnDestroy() override;

private:
	// Movement

	const float m_accelerationSpeed = 500.0f;
	const float m_maxSpeed = 100.0f;

	// Gun
	const float s_shootDelay = 0.5f;
	float m_shootCooldown = 0.0f;

	//Respawn
	int m_alphaDirection = -1;
	const int m_minAlpha = 50;
	const int m_alphaChangeSpeed = 200;
	sf::Uint8 m_currentAlpha = 255;

	// Score
	int m_currentScore = 0;

	void UpdateMovement(float dt);
	void UpdateGun(float dt);
};

