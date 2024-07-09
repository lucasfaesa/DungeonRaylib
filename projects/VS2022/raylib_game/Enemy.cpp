#include "Enemy.h"

Enemy::Enemy(Vector3 pos, Vector3 size, float maxSpeed, Vector3& targetPos, const BoundingBox& targetBoudingBox, float attackRadius, float detectionRadius, Player& player) :
	Agent(pos, size, maxSpeed, targetPos, targetBoudingBox, attackRadius, detectionRadius), _player(&player)
{

}

void Enemy::Update(float deltaTime)
{
	Agent::Update(deltaTime);

	if (_isTargetInsideDetectionRadius) {
		FollowTarget(deltaTime);
		CountAttackTimer(deltaTime);
	}

	if (_isTargetInsideAttackRadius) {
		AttackPlayer(deltaTime);
	}
}

void Enemy::AttackPlayer(float deltaTime)
{
	if (attackTimer >= attackDelay) {
		attackTimer = 0;
		_player->TakeDamage(_attackDamage);
	}
}

void Enemy::CountAttackTimer(float deltaTime)
{
	attackTimer += deltaTime;
}
