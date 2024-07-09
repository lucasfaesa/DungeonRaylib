#pragma once
#include "Agent.h"
#include "Player.h"

class Enemy : public Agent {

public:
	Enemy() = default;
	Enemy(Vector3 pos, Vector3 size, float maxSpeed, Vector3& targetPos,
		const BoundingBox& targetBoudingBox, float attackRadius, float detectionRadius, Player& player);

	void Update(float deltaTime) override;
	void AttackPlayer(float deltaTime);
	void CountAttackTimer(float deltaTime);
private:
	Player* _player;
	float attackDelay{ 2.f };
	float attackTimer{0.f};
	int _attackDamage{ 5 };
};