#include "Damageable.h"

Damageable::Damageable(int maxHealth):
	_maxHealth(maxHealth), _currentHealth(maxHealth)
{
}


bool Damageable::GetIsDead() const
{
	return _isDead;
}

float Damageable::GetInvincibilityTime() const
{
	return _invincibilityTime;
}

void Damageable::DrawHealth()
{
	float healthBarPercent = (float)_currentHealth / (float)_maxHealth;

	DrawText("HEALTH", 17, 730, 20, WHITE);
	DrawRectangle(15, 750, 300 * healthBarPercent, 30, RED);
	DrawRectangleLines(15, 750, 301, 31, BLACK);
}

void Damageable::TakeDamage(int value)
{
	if (GetTime() - _lastDamageReceivedTime <= _invincibilityTime ||
		_isDead) 
		return;

	_lastDamageReceivedTime = GetTime();

	_currentHealth -= value;

	if (_currentHealth <= 0) {
		_currentHealth = 0;
		SetDead();
		
	}

	std::cout << "took damage: " << value << " current health: " << _currentHealth << std::endl;
}

void Damageable::SetDead()
{
	_isDead = true;
	std::cout << "died" << std::endl;
}

