#pragma once

class Damageable {
public:

	Damageable() = default;
	Damageable(int maxHealth);

	bool GetIsDead() const;

	int TakeDamage(int value);

protected:
	const int _maxHealth{ };

	int _currentHealth{ };

	bool _isDead{ false };
};