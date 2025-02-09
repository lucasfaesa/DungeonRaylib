#pragma once

#include <list>

#include "raylib.h"
#include "IBehavior.h"
#include "raymath.h"
#include "Collideable.h"
#include "SeekBehavior.h"
#include "World.h"

class IBehavior;
class SeekBehavior;

class Agent {

public:
	
	Agent() = default;
	Agent(Vector3 pos, Vector3 size, Vector3& targetPos, const BoundingBox& targetBoudingBox);

	virtual ~Agent() = default;

	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual void CheckTargetInsideDetectionRadius();
	virtual void CheckTargetInsideAttackRadius();


	void SetSeekBehavior(SeekBehavior* behavior);
	void SetPosition(Vector3 pos);
	Vector3 GetPosition() const;
	float GetMaxSpeed() const;

	const BoundingBox& GetBodyBoundingBox();
	const BoundingBox& GetFeetBoundingBox();

	void UpdateColliderPosition();

	Vector3 acceleration{};
	Vector3 velocity{};

protected:
	virtual void FollowTarget(float deltaTime);
	void GravityControl(float deltaTime);

protected:
	Vector3 _position{ 0.f,0.f };
	Vector3 _size{};
	Vector3* _targetPosition{nullptr};
	const BoundingBox* _targetBoundingBox{ nullptr };
	float _attackRadius{};
	float _detectionRadius{};
	Color _color{ BLUE };

	bool _isTargetInsideDetectionRadius{false};
	bool _isTargetInsideAttackRadius{false};

	float _maxSpeed{};

	Collideable bodyCollideable;
	Collideable groundCollideable;

	SeekBehavior* _seekBehavior{ nullptr };

	Vector3 _attackRadiusPos;

	bool isGrounded{ false };
	float terminalMoveDeltaY{ 0.3f }; //or 0.125f
	float fallSpeed{};
	float gravityRate{ 0.05f };
	float gravity{ World::gravity };



private:
	
};