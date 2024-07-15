#include "Enemy.h"

//Enemy::idleTexture = LoadTexture("../resources/enemy/frogmon_stand.png");
//Enemy::walkTexture = LoadTexture("../resources/enemy/frogmon_walk.png");
//Enemy::dieTexture = LoadTexture("../resources/enemy/frogmon_die.png");

Texture2D Enemy::idleTexture;
Texture2D Enemy::walkTexture;
Texture2D Enemy::dieTexture;

Enemy::Enemy(Vector3 pos, Vector3 size, Player& player) :
	Agent(pos, size, player.GetPlayerPosition(), player.GetBodyCollideable().GetCollider()), _player(&player), _camera(&player.GetPlayerCamera()),
	Damageable(100)
{
	switch((int)size.y)
	{
		case 1:
			_maxSpeed = 30.f;
			attackDelay = 0.7f;
			_attackDamage = 2.f;
			_attackRadius = 1.4f;
			_detectionRadius = 11.f;
			_maxHealth = 35.f;
			break;
		case 2:
			_maxSpeed = 15.f;
			attackDelay = 1.5f;
			_attackDamage = 4.f;
			_attackRadius = 1.7f;
			_detectionRadius = 9.5f;
			_maxHealth = 60.f;
			break;
		case 3:
			_maxSpeed = 9.f;
			attackDelay = 2.f;
			_attackDamage = 5.f;
			_attackRadius = 2.f;
			_detectionRadius = 10.f;
			_maxHealth = 100.f;
			break;
		case 4:
			_maxSpeed = 6.f;
			attackDelay = 2.5f;
			_attackDamage = 8.f;
			_attackRadius = 2.5f;
			_detectionRadius = 10.f;
			_maxHealth = 140.f;
			break;
		default:
			_maxSpeed = 4.f;
			attackDelay = 3.f;
			_attackDamage = 18.f;
			_attackRadius = 8.f;
			_detectionRadius = 14.f;
			_maxHealth = 1000.f;
			break;
	}

	_currentHealth = _maxHealth;
	_size.x = size.y * 0.5f;
	_size.z = size.y * 0.5f;

	if(idleTexture.height == 0 || idleTexture.width == 0)
	{
		idleTexture = LoadTexture("../resources/enemy/frogmon_stand.png");
		walkTexture = LoadTexture("../resources/enemy/frogmon_walk.png");
		dieTexture = LoadTexture("../resources/enemy/frogmon_die.png");
	}

	frameRec = { 0.0f, 0.0f, (float)idleTexture.width / idleTotalFrames, (float)idleTexture.height };

	initialPosition = pos;
}

void Enemy::Update(float deltaTime)
{
	lastPositionBeforeBodyCollision = _position;

	if (_isDead && !preparingToDie) 
		return;

	
	gravity = isGrounded || preparingToDie || _isDead || !calculatePhysics ? 0.f : World::gravity;
	GravityControl(deltaTime);

	Agent::Update(deltaTime);

	

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

	drawColor = GetTime() - damageTookTime >= damageFeedbackDuration ? WHITE : RED;
																											//just to be squared, used two y's
	DrawBillboardRec(*_camera, *currentTexture, frameRec, { _position.x, _position.y + _size.y * 0.5f, _position.z }, { _size.y, _size.y }, drawColor);
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
	//std::cout << "is grounded false enemy" << std::endl;
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
			calculatePhysics = false;
			followingPlayer = false;
			currentAnimationFrameSpeed = idleFramesSpeed;
			currentAnimationTotalFrames = idleTotalFrames;
			currentTexture = &idleTexture;
			frameRec = { 0.0f, 0.0f, (float)idleTexture.width / idleTotalFrames, (float)idleTexture.height };
			break;
		case State::WALKING:
			followingPlayer = true;
			calculatePhysics = true;
			currentAnimationFrameSpeed = walkFramesSpeed;
			currentAnimationTotalFrames = walkTotalFrames;
			currentTexture = &walkTexture;
			frameRec = { 0.0f, 0.0f, (float)walkTexture.width / walkTotalFrames, (float)walkTexture.height };
			break;
		case State::DEAD:
			calculatePhysics = false;
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
			//bodyCollideable = {};
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

void Enemy::SetCalculatePhysics(bool status)
{
	calculatePhysics = status;
}

void Enemy::TakeDamage(int value)
{
	Damageable::TakeDamage(value);

	damageTook = true;
	damageTookTime = GetTime();
}

void Enemy::OnGameRestarted()
{
	_position = initialPosition;
	_currentHealth = _maxHealth;
	ChangeCurrentState(State::IDLE);
	_isDead = false;
	preparingToDie = false;

}
