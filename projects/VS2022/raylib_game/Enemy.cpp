#include "Enemy.h"

Enemy::Enemy(Vector3 pos, Vector3 size, float maxSpeed, Vector3& targetPos, const BoundingBox& targetBoudingBox, float attackRadius, float detectionRadius, Player& player, Camera& camera) :
	Agent(pos, size, maxSpeed, targetPos, targetBoudingBox, attackRadius, detectionRadius), _player(&player), _camera(&camera)
{

}

void Enemy::Update(float deltaTime)
{
	Agent::Update(deltaTime);

	//return;

	if (_isTargetInsideDetectionRadius) {
		FollowTarget(deltaTime);
		CountAttackTimer(deltaTime);
	}

	if (_isTargetInsideAttackRadius) {
		AttackPlayer(deltaTime);
	}

	CountAnimationFrames(deltaTime);
}

void Enemy::Draw()
{
	Agent::Draw();
	//DrawBillboard(*_camera, walkTexture, { _position.x, _position.y + _size.y * 0.5f, _position.z }, _size.y, WHITE);
	DrawBillboardRec(*_camera, walkTexture, frameRec, { _position.x, _position.y + _size.y * 0.5f, _position.z }, { _size.y, _size.y }, WHITE);
}

void Enemy::OnApplicationQuit()
{
	UnloadTexture(walkTexture);
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

void Enemy::SetDistanceFromPlayer()
{
	_distanceFromPlayer = Vector3Distance(_camera->position, this->_position);
}

float Enemy::GetDistanceFromPlayer() const
{
	return _distanceFromPlayer;
}

void Enemy::CountAnimationFrames(float deltaTime)
{
	framesCounter++;

	if (framesCounter >= (60 / walkFramesSpeed)) {

		framesCounter = 0;
		currentFrame++;

		if (currentFrame > 4) currentFrame = 0;

		frameRec.x = (float)currentFrame * (float)walkTexture.width / 4;

	}
}
