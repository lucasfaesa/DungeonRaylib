#pragma once

#include <list>

#include "raylib.h"
#include "IBehavior.h"
#include "raymath.h"

class IBehavior;

class Agent {

public:
	float maxSpeed{ 50.f };
	Vector3 acceleration;
	Vector3 velocity;
	
	Agent() = default;
	Agent(Vector3 pos, Vector3& playerPos, float radius, Color color);

	virtual ~Agent() {};

	virtual void Update(float deltaTime);
	virtual void Draw();

	void AddBehavior(IBehavior* behavior);
	void SetPosition(Vector3 pos);
	Vector3 GetPosition();

private:
	Vector3 _position{ 0.f,0.f };
	Vector3* playerPosition{nullptr};
	float _radius{ 5.f };
	Color _color{ BLUE };

	std::list<IBehavior*> _behaviors;
};