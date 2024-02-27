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

	void OnDestroy() override;

private:
	// Movement

	static constexpr float s_accelerationSpeed = 2000.0f;
	static constexpr float s_maxSpeed = 750.0f;


	// Gun
	static constexpr float s_shootDelay = 0.1f;
	float m_shootCooldown = 0.0f;

	// Health

	static constexpr int s_maxLives = 3;

	// Score
	int m_currentScore = 0;

	void UpdateMovement(float dt);

};

