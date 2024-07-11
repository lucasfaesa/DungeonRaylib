#include "SeekBehavior.h"
#include <iostream>

SeekBehavior::SeekBehavior(Vector3& target):
	_target(&target)
{

}

void SeekBehavior::Update(Agent* agent, float deltaTime)
{

	if (_canSeek) {
		Vector3 direction = Vector3Subtract(*_target, agent->GetPosition());
		float distance = Vector3Length(direction);

		// Implement a slowing radius
		float slowingRadius = 10.0f; // Adjust as needed

		// Calculate desired speed
		float desiredSpeed = agent->GetMaxSpeed();
		if (distance < slowingRadius) {
			desiredSpeed = agent->GetMaxSpeed() * (distance / slowingRadius);
		}

		// Calculate desired velocity
		Vector3 desiredVelocity = Vector3Scale(Vector3Normalize(direction), desiredSpeed);

		// Calculate steering force
		Vector3 steering = Vector3Subtract(desiredVelocity, agent->velocity);
		agent->acceleration = Vector3Scale(steering, 1.0f / deltaTime); // Adjust steering force scaling as needed
	}
	else {
		// Optionally stop the agent if seeking is disabled
		agent->velocity = { 0.f, 0.f, 0.f };
	}
	/*
	if (_canSeek) {
		Vector3 direction = Vector3Subtract(*_target, agent->GetPosition());
		agent->acceleration = Vector3Scale(Vector3Normalize(direction), (agent->GetMaxSpeed() * deltaTime));
	}
	else {
		
		agent->velocity.x = 0;
		agent->velocity.z = 0;
		//std::cout << "here: " << distance << std::endl;
	}
	*/

	//std::cout << _target->x << " " << _target->y << " " << _target->z << std::endl;
	//std::cout << "distance: " << distance << std::endl;
}

void SeekBehavior::SetCanSeek(bool status)
{
	_canSeek = status;
}

float SeekBehavior::GetDampener(float distance)
{
	
	float threshold = 5.0f; // Distance at which dampener starts decreasing
	float minDampener = 0.2f;  // Minimum dampener value

	if (distance <= threshold) {
		return minDampener + (1.0f - minDampener) * (distance / threshold);
	}
	else {
		return 1.0f;
	}
	
}
