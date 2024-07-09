#include "SeekBehavior.h"
#include <iostream>

SeekBehavior::SeekBehavior(Vector3& target):
	_target(&target)
{

}

void SeekBehavior::Update(Agent* agent, float deltaTime)
{
	//if (!_canSeek) return;

	//float distance = Vector3Distance(*_target, agent->GetPosition());

	if (_canSeek) {
		Vector3 direction = Vector3Subtract(*_target, agent->GetPosition());
		agent->acceleration = Vector3Scale(Vector3Normalize(direction), (agent->GetMaxSpeed() * deltaTime));
	}
	else {
		
		agent->velocity.x = 0;
		agent->velocity.z = 0;
		//std::cout << "here: " << distance << std::endl;
	}
	

	//std::cout << _target->x << " " << _target->y << " " << _target->z << std::endl;
	//std::cout << "distance: " << distance << std::endl;
}

void SeekBehavior::SetCanSeek(bool status)
{
	_canSeek = status;
}
