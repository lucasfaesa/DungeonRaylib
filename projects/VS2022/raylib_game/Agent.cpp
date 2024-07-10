#include "Agent.h"
//#include <iostream>

Agent::Agent(Vector3 pos, Vector3 size, float maxSpeed, Vector3& targetPos, const BoundingBox& targetBoundingBox, float attackRadius, float detectionRadius):
	_position(pos), _size(size), _maxSpeed(maxSpeed), _targetPosition(&targetPos), _targetBoundingBox(&targetBoundingBox),
	_attackRadius(attackRadius), _detectionRadius(detectionRadius)
{
	_targetPosition = &targetPos;

	Vector3 bodyMin{ _position.x - _size.x * 0.5f, _position.y, _position.z - _size.z * 0.5f };
	Vector3 bodyMax{ _position.x + _size.x * 0.5f, _position.y + _size.y, _position.z + _size.z * 0.5f };

	bodyCollideable = Collideable{ BoundingBox{ bodyMin , bodyMax } , Layers::Layer::AGENT };
}

void Agent::Update(float deltaTime)
{
	
}

void Agent::Draw()
{
	DrawSphereWires(_position, _attackRadius, 10, 10, _isTargetInsideAttackRadius ? MAGENTA : GREEN);

	DrawSphereWires(_position, _detectionRadius, 10, 10, _isTargetInsideDetectionRadius ? MAGENTA : GREEN);

	DrawBoundingBox(bodyCollideable.GetCollider(), YELLOW);
}

void Agent::CheckTargetInsideDetectionRadius()
{
	_isTargetInsideDetectionRadius = CheckCollisionBoxSphere(*_targetBoundingBox, _position, _detectionRadius);
}

void Agent::CheckTargetInsideAttackRadius()
{
	_isTargetInsideAttackRadius = CheckCollisionBoxSphere(*_targetBoundingBox, _position, _attackRadius);
	_seekBehavior->SetCanSeek(!_isTargetInsideAttackRadius);
}

void Agent::FollowTarget(float deltaTime)
{
	_seekBehavior->Update(this, deltaTime);

	//std::cout << playerPosition->x << " " <<playerPosition->y << " " <<playerPosition->z << std::endl;

	velocity.x += acceleration.x;
	velocity.z += acceleration.z;

	if (Vector3Length(velocity) > _maxSpeed) {
		velocity = Vector3Scale(Vector3Normalize(velocity), _maxSpeed);
	}

	_position.x += velocity.x * deltaTime;
	_position.z += velocity.z * deltaTime;

	acceleration = { 0.f, 0.f };

	UpdateColliderPosition();
}

void Agent::UpdateColliderPosition()
{
	bodyCollideable.UpdateBoundingBox(Vector3{ _position.x - _size.x * 0.5f, _position.y, _position.z - _size.z * 0.5f },
		Vector3{ _position.x + _size.x * 0.5f, _position.y + _size.y, _position.z + _size.z * 0.5f });
}

void Agent::SetSeekBehavior(SeekBehavior* behavior)
{
	_seekBehavior = behavior;
}

void Agent::SetPosition(Vector3 pos)
{
	_position = pos;
}

Vector3 Agent::GetPosition()
{
	return _position;
}

float Agent::GetMaxSpeed() const
{
	return _maxSpeed;
}

const BoundingBox& Agent::GetBoundingBox()
{
	return bodyCollideable.GetCollider();
}

