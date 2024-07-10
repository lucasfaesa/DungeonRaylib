#pragma once

#include <iostream>
#include <raylib.h>

class Damageable {
public:

	Damageable() = default;
	Damageable(int maxHealth);

	bool GetIsDead() const;
	float GetInvincibilityTime() const;

	virtual void TakeDamage(int value);

	virtual void SetDead();

protected:
	const int _maxHealth{ };

	int _currentHealth{ };

	float _invincibilityTime{ 0.6f };

	bool _isDead{ false };

	double _lastDamageReceivedTime {};
};