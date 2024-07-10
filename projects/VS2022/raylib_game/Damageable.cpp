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

	//std::cout << "took damage: " << value << " current health: " << _currentHealth << std::endl;
}

void Damageable::SetDead()
{
	_isDead = true;
	std::cout << "died" << std::endl;
}
