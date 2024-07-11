#include "Enemy.h"

Enemy::Enemy(Vector3 pos, Vector3 size, float maxSpeed, Vector3& targetPos, const BoundingBox& targetBoudingBox, float attackRadius, float detectionRadius, Player& player, Camera& camera) :
	Agent(pos, size, maxSpeed, targetPos, targetBoudingBox, attackRadius, detectionRadius), _player(&player), _camera(&camera),
	Damageable(100)
{
	frameRec = { 0.0f, 0.0f, (float)idleTexture.width / idleTotalFrames, (float)idleTexture.height };
}

void Enemy::Update(float deltaTime)
{
	lastPositionBeforeBodyCollision = _position;

	Agent::Update(deltaTime);

	if (_isDead && !preparingToDie) 
		return;
	

	if (!preparingToDie) {

		if(IsOnWaitBeforeWalkingTime())
		{
			ChangeCurrentState(State::IDLE);
		}else
		{
			if (_isTargetInsideDetectionRadius) {
				FollowTarget(deltaTime);
				ChangeCurrentState(State::WALKING);
				CountAttackTimer(deltaTime);
			}
			else {
				ChangeCurrentState(State::IDLE);
			}
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

float Enemy::GetDistanceFromPlayer() const
{
	return Vector3Distance(_camera->position, this->_position);
}

void Enemy::SetDead()
{
	Damageable::SetDead();
	preparingToDie = true;
	ChangeCurrentState(State::DEAD);
}

void Enemy::OnCollisionOnBody()
{
	

	isCollidingBody = true;
	
	ForcePositionXZChange();
}

void Enemy::OnCollisionOnFoot(float topYPos)
{
	isGrounded = true;
	fallSpeed = 0;

	ForcePositionYChange(topYPos);
}

void Enemy::LeftCollisionOnFoot()
{
	std::cout << "is grounded false enemy" << std::endl;
	isGrounded = false;
}

void Enemy::WaitBeforeWalkingAgain()
{
	waitBeforeWalkingTimer = GetTime();
}

void Enemy::ChangeCurrentState(State newState)
{
	if (newState == currentState) return;

	currentState = newState;

	framesCounter = 0;
	currentFrame = 0;

	switch (newState) {
		case State::IDLE:
			followingPlayer = false;
			currentAnimationFrameSpeed = idleFramesSpeed;
			currentAnimationTotalFrames = idleTotalFrames;
			currentTexture = &idleTexture;
			frameRec = { 0.0f, 0.0f, (float)idleTexture.width / idleTotalFrames, (float)idleTexture.height };
			break;
		case State::WALKING:
			followingPlayer = true;
			currentAnimationFrameSpeed = walkFramesSpeed;
			currentAnimationTotalFrames = walkTotalFrames;
			currentTexture = &walkTexture;
			frameRec = { 0.0f, 0.0f, (float)walkTexture.width / walkTotalFrames, (float)walkTexture.height };
			break;
		case State::DEAD:
			followingPlayer = false;
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
		frameRec.x = static_cast<float>(currentFrame) * static_cast<float>(currentTexture->width) / currentAnimationTotalFrames;

		if (currentState == State::DEAD && currentFrame == currentAnimationTotalFrames - 1) {
			preparingToDie = false;
			bodyCollideable = {};
			return;
		}

	}
}

void Enemy::ForcePositionXZChange()
{
	_position.x = lastPositionBeforeBodyCollision.x;
	_position.z = lastPositionBeforeBodyCollision.z;

	velocity.x = 0;
	velocity.z = 0;


	UpdateColliderPosition();
}

void Enemy::ForcePositionYChange(float topYPos)
{
	//								offset to not make the body collider hit the ground//strctures from above
	_position.y = topYPos + 0.01f;
}

bool Enemy::IsOnWaitBeforeWalkingTime()
{

	return GetTime() - waitBeforeWalkingTimer <= waitBeforeWalkingDuration;
}

bool Enemy::IsFollowingPlayer()
{
	return followingPlayer;
}
