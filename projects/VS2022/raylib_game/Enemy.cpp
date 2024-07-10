#include "Enemy.h"

Enemy::Enemy(Vector3 pos, Vector3 size, float maxSpeed, Vector3& targetPos, const BoundingBox& targetBoudingBox, float attackRadius, float detectionRadius, Player& player, Camera& camera) :
	Agent(pos, size, maxSpeed, targetPos, targetBoudingBox, attackRadius, detectionRadius), _player(&player), _camera(&camera),
	Damageable(100)
{
	frameRec = { 0.0f, 0.0f, (float)idleTexture.width / idleTotalFrames, (float)idleTexture.height };
}

void Enemy::Update(float deltaTime)
{
	Agent::Update(deltaTime);

	if (isDead) return;
	//return;

	if (!preparingToDie) {
		if (_isTargetInsideDetectionRadius) {
			FollowTarget(deltaTime);
			ChangeCurrentState(State::WALKING);
			CountAttackTimer(deltaTime);
		}
		else {
			ChangeCurrentState(State::IDLE);
		}

		if (_isTargetInsideAttackRadius) {
			ChangeCurrentState(State::IDLE);
			AttackPlayer(deltaTime);
		}
	}
	
	/*if (IsKeyPressed(KEY_R)) {
		std::cout << "preparing to die: " << std::endl;
		ChangeCurrentState(State::DEAD);
		preparingToDie = true;
	}*/

	CountAnimationFrames(deltaTime);
}

void Enemy::Draw()
{
	Agent::Draw();
																											//just to be squared, used two y's
	DrawBillboardRec(*_camera, *currentTexture, frameRec, { _position.x, _position.y + _size.y * 0.5f, _position.z }, { _size.y, _size.y }, WHITE);
}

void Enemy::OnApplicationQuit()
{
	UnloadTexture(walkTexture);
	UnloadTexture(dieTexture);
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

void Enemy::ChangeCurrentState(State newState)
{
	if (newState == currentState) return;

	currentState = newState;

	framesCounter = 0;
	currentFrame = 0;

	switch (newState) {
		case State::IDLE:
			currentAnimationFrameSpeed = idleFramesSpeed;
			currentAnimationTotalFrames = idleTotalFrames;
			currentTexture = &idleTexture;
			frameRec = { 0.0f, 0.0f, (float)idleTexture.width / idleTotalFrames, (float)idleTexture.height };
			break;
		case State::WALKING:
			currentAnimationFrameSpeed = walkFramesSpeed;
			currentAnimationTotalFrames = walkTotalFrames;
			currentTexture = &walkTexture;
			frameRec = { 0.0f, 0.0f, (float)walkTexture.width / walkTotalFrames, (float)walkTexture.height };
			break;
		case State::DEAD:
			currentAnimationFrameSpeed = dyingFramesSpeed;
			currentAnimationTotalFrames = dyingTotalFrames;
			currentTexture = &dieTexture;
			frameRec = { 0.0f, 0.0f, (float)dieTexture.width / dyingTotalFrames, (float)dieTexture.height };
			break;
	}
}

void Enemy::CountAnimationFrames(float deltaTime)
{
	framesCounter++;

	if (framesCounter >= (60 / currentAnimationFrameSpeed)) {

		framesCounter = 0;
		currentFrame++;

		if (currentFrame > currentAnimationTotalFrames - 1) currentFrame = 0;

		//std::cout << "current Frame: " << currentFrame << std::endl;
		frameRec.x = (float)currentFrame * (float)currentTexture->width / currentAnimationTotalFrames;

		if (currentState == State::DEAD && currentFrame == currentAnimationTotalFrames - 1) {
			isDead = true;
			return;
		}

	}
}
