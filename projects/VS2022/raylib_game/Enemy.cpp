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
	}
}
