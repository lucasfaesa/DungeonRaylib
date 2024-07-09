#pragma once

#include "raylib.h"
#include "Agent.h"

class Agent;

class IBehavior {
public:
	IBehavior() = default;
	~IBehavior() = default;

	virtual void Update(Agent* agent, float deltaTime);
};