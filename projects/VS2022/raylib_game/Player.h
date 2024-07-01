#pragma once
#include "CameraManager.h"
#include "World.h"
#include "Layers.h"
#include "Collideable.h"
#include "RectangleF.h"

class Player {

public:
	Player() = default;
	Player(Vector3 pos, Vector3 rot);
	void ReadInput();
	void Update(const float deltaTime);
	void Draw();
	void OnCollisionOnBody();
	void OnCollisionOnFoot(RectangleF& collideable);
	void LeftCollisionOnFoot();
	Collideable& GetBodyCollideable();
	Collideable& GetFootCollideable();

private:

	void InputMovement();
	void InputLook();
	void InputJump();

	void HandleJump(float deltaTime);

	void UpdatePlayerRotation();
	void UpdatePlayerPosition();
	void UpdateColliderPosition();
	void ForcePositionXZChange();
	void ForcePositionYChange(float topYPos);

	Camera* camera{ nullptr };

	//static constexpr Layers::Layer layer = Layers::Layer::PLAYER;

	static constexpr float speed = 5.f;
	static constexpr Vector3 size{ 0.5f, 1.8f, 0.5f };
	static constexpr float jumpForce = 1.f;
	static constexpr float jumpDuration = 0.4f;

	Vector3 position{ };
	Vector3 rotation{ };

	Vector3 lastPositionBeforeBodyCollision;
	float lastPositionBeforeFootCollision;

	Vector3 moveDelta{};
	Vector3 mouseDelta{};
	Vector2 mouseSensivity{ 0.05f , 0.05f };

	//bool isColliding{ false };

	//BoundingBox boxCollider;
	//BoundingBox groundCollider;

	Collideable bodyCollideable;
	Collideable groundCollideable;

	float gravity = World::gravity;

	bool isGrounded{false};
	bool canJump{ false };
	bool isJumping{ false };
	float jumpTimer{};

	bool isCollidingBody;
};