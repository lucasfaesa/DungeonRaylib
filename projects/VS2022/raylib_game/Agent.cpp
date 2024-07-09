#include "Agent.h"
//#include <iostream>

Agent::Agent(Vector3 pos, Vector3& playerPos, float radius, Color color):
	_position(pos), _radius(radius), _color(color)
{
	playerPosition = &playerPos;
}

void Agent::Update(float deltaTime)
{
	for (auto it = _behaviors.begin(); it != _behaviors.end(); it++)
	{
		(*it)->Update(this, deltaTime);
	}

	//std::cout << playerPosition->x << " " <<playerPosition->y << " " <<playerPosition->z << std::endl;

	velocity.x += acceleration.x;
	//velocity.y += acceleration.y;
	velocity.z += acceleration.z;

	if (Vector3Length(velocity) > maxSpeed) {
		velocity = Vector3Scale(Vector3Normalize(velocity), maxSpeed);
	}

	_position.x += velocity.x * deltaTime;
	//_position.y += velocity.y * deltaTime;
	_position.z += velocity.z * deltaTime;

	acceleration = { 0.f, 0.f };
}

void Agent::Draw()
{
	DrawSphereWires(_position, _radius, 10, 10, _color);
}

void Agent::AddBehavior(IBehavior* behavior)
{
	_behaviors.push_back(behavior);
}

void Agent::SetPosition(Vector3 pos)
{
	_position = pos;
}

Vector3 Agent::GetPosition()
{
	return _position;
}

