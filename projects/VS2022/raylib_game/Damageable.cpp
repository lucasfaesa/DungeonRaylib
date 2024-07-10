#include "Damageable.h"

Damageable::Damageable(int maxHealth):
	_maxHealth(maxHealth), _currentHealth(maxHealth)
{
}


bool Damageable::GetIsDead() const
{
	return _isDead;
}

int Damageable::TakeDamage(int value)
{
	_currentHealth -= value;

	if (_currentHealth <= 0) {
		_currentHealth = 0;
		_isDead = true;
	}

	return _currentHealth;
}
