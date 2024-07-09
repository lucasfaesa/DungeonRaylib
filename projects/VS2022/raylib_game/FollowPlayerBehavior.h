#pragma once

#include "raylib.h"
#include "IBehavior.h"
#include "Player.h"

//class Agent;

class FollowPlayerBehavior : public IBehavior {
public:
	FollowPlayerBehavior() = default;
	~FollowPlayerBehavior() = default;

	virtual void Update(Agent* agent, Vector3& playerPos, float deltaTime);

private:
	//Player* _target;
};