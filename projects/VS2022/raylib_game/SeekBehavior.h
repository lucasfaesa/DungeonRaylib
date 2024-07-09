#pragma once

#include "raylib.h"
#include "IBehavior.h"

class Agent;

class SeekBehavior : public IBehavior {

public:
	SeekBehavior() = default;
	SeekBehavior(Vector3& target);
	~SeekBehavior() = default;

	virtual void Update(Agent* agent, float deltaTime);

private:
	Vector3* _target;
};