#include "Agent.h"


//#include <iostream>

Agent::Agent(Vector3 pos, Vector3 size, float maxSpeed, Vector3& targetPos, const BoundingBox& targetBoundingBox, float attackRadius, float detectionRadius):
	_position(pos), _size(size), _maxSpeed(maxSpeed), _targetPosition(&targetPos), _targetBoundingBox(&targetBoundingBox),
	_attackRadius(attackRadius), _detectionRadius(detectionRadius)
{
	_targetPosition = &targetPos;

	Vector3 bodyMin{ _position.x - _size.x * 0.5f, _position.y, _position.z - _size.z * 0.5f };
	Vector3 bodyMax{ _position.x + _size.x * 0.5f, _position.y + _size.y, _position.z + _size.z * 0.5f };

	Vector3 groundMin{ _position.x - (size.x - 0.03f) * 0.5f, _position.y - 0.1f, _position.z - (size.z - 0.03f) * 0.5f };
	Vector3 groundMax{ _position.x + (size.x - 0.03f) * 0.5f, _position.y, _position.z + (size.z - 0.03f) * 0.5f };

	bodyCollideable = Collideable{ BoundingBox{ bodyMin , bodyMax } , Layers::Layer::AGENT };
	groundCollideable = Collideable{ BoundingBox{ groundMin , groundMax } , Layers::Layer::DEFAULT };
}

void Agent::Update(float deltaTime)
{
	gravity = isGrounded ? 0.f : World::gravity;
	GravityControl(deltaTime);
	UpdateColliderPosition();
}

void Agent::Draw()
{
	//DrawSphereWires(_attackRadiusPos, _attackRadius, 10, 10, _isTargetInsideAttackRadius ? MAGENTA : GREEN);

	//DrawSphereWires(_position, _detectionRadius, 10, 10, _isTargetInsideDetectionRadius ? MAGENTA : GREEN);

	DrawBoundingBox(bodyCollideable.GetCollider(), YELLOW);
	DrawBoundingBox(groundCollideable.GetCollider(), isGrounded ? GREEN : MAGENTA);
}

void Agent::CheckTargetInsideDetectionRadius()
{

	_isTargetInsideDetectionRadius = CheckCollisionBoxSphere(*_targetBoundingBox, _position, _detectionRadius);
}

void Agent::CheckTargetInsideAttackRadius()
{
	_attackRadiusPos = { _position.x, _position.y + _size.y * 0.5f , _position.z };

	_isTargetInsideAttackRadius = CheckCollisionBoxSphere(*_targetBoundingBox, _attackRadiusPos, _attackRadius);
	_seekBehavior->SetCanSeek(!_isTargetInsideAttackRadius);
}

void Agent::FollowTarget(float deltaTime)
{
	_seekBehavior->Update(this, deltaTime);

	velocity.x += acceleration.x * deltaTime;
	velocity.z += acceleration.z * deltaTime;

	// Apply damping to velocity
	float damping = 0.9f; // Adjust damping factor as needed
	velocity = Vector3Scale(velocity, damping);

	// Limit velocity to max speed
	float currentSpeed = Vector3Length(velocity);
	if (currentSpeed > _maxSpeed) {
		velocity = Vector3Scale(velocity, _maxSpeed / currentSpeed);
	}

	_position.x += velocity.x * deltaTime;
	_position.z += velocity.z * deltaTime;

	// Reset acceleration after applying it
	acceleration = { 0.f, 0.f };

	UpdateColliderPosition();

	/*_seekBehavior->Update(this, deltaTime);

	//std::cout << playerPosition->x << " " <<playerPosition->y << " " <<playerPosition->z << std::endl;

	velocity.x += acceleration.x;
	velocity.z += acceleration.z;

	if (Vector3Length(velocity) > _maxSpeed) {
		velocity = Vector3Scale(Vector3Normalize(velocity), _maxSpeed);
	}

	_position.x += velocity.x * deltaTime;
	_position.z += velocity.z * deltaTime;

	acceleration = { 0.f, 0.f };

	UpdateColliderPosition();*/
}

void Agent::GravityControl(float deltaTime)
{
	if (!isGrounded) {
		fallSpeed += gravity * gravityRate * deltaTime;

		_position.y -= fallSpeed;
	}
}

void Agent::UpdateColliderPosition()
{
	bodyCollideable.UpdateBoundingBox(Vector3{ _position.x - _size.x * 0.5f, _position.y, _position.z - _size.z * 0.5f },
		Vector3{ _position.x + _size.x * 0.5f, _position.y + _size.y, _position.z + _size.z * 0.5f });

	groundCollideable.UpdateBoundingBox(Vector3{ _position.x - (_size.x - 0.03f) * 0.5f, _position.y - 0.1f, _position.z - (_size.z - 0.03f) * 0.5f },
		Vector3{ _position.x + (_size.x - 0.03f) * 0.5f, _position.y, _position.z + (_size.z - 0.03f) * 0.5f });
}

void Agent::SetSeekBehavior(SeekBehavior* behavior)
{
	_seekBehavior = behavior;
}

void Agent::SetPosition(Vector3 pos)
{
	_position = pos;
}

Vector3 Agent::GetPosition() const
{
	return _position;
}

float Agent::GetMaxSpeed() const
{
	return _maxSpeed;
}

const BoundingBox& Agent::GetBodyBoundingBox()
{
	return bodyCollideable.GetCollider();
}

const BoundingBox& Agent::GetFeetBoundingBox()
{
	return groundCollideable.GetCollider();
}

