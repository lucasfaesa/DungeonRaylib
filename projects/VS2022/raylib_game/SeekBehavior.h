#pragma once

#include "raylib.h"
#include "Agent.h"

class Agent;

class SeekBehavior {

public:
	SeekBehavior() = default;
	SeekBehavior(Vector3& target);
	~SeekBehavior() = default;

	virtual void Update(Agent* agent, float deltaTime);
	void SetCanSeek(bool status);

private:
	Vector3* _target;
	bool _canSeek{ false };
};